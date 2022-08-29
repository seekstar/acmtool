// https://www.luogu.com.cn/record/85252853
// 433ms
#[derive(Clone, PartialEq)]
struct SplayNode<T> {
    c: [u32; 2],
    // Number of elements in this node
    cnt: u32,
    // Number of elements in the subtree
    scnt: u32,
    key: T,
}

impl<T: std::default::Default> Default for SplayNode<T> {
    fn default() -> SplayNode<T> {
        SplayNode {
            c: [0; 2],
            cnt: 0,
            scnt: 0,
            key: T::default(),
        }
    }
}

impl<T> SplayNode<T> {
    fn new(key: T) -> SplayNode<T> {
        SplayNode {
            c: [0; 2],
            cnt: 1,
            scnt: 1,
            key: key,
        }
    }
}

struct Splay<T> {
    s: Vec<SplayNode<T>>,
    root: u32,
}

impl<T: std::default::Default + std::cmp::Ord> Splay<T> {
    fn with_capacity(n: usize) -> Splay<T> {
        let mut s = Vec::with_capacity(n);
        s.push(SplayNode::<T>::default());
        Splay { s, root: 0 }
    }
    fn lc(&self, rt: u32) -> u32 {
        self.s[rt as usize].c[0]
    }
    fn rc(&self, rt: u32) -> u32 {
        self.s[rt as usize].c[1]
    }
    fn push_up(&mut self, rt: u32) {
        self.s[rt as usize].scnt = self.s[rt as usize].cnt;
        // if self.lc(rt) != 0 {
        self.s[rt as usize].scnt += self.s[self.lc(rt) as usize].scnt;
        // }
        // if self.rc(rt) != 0 {
        self.s[rt as usize].scnt += self.s[self.rc(rt) as usize].scnt;
        // }
    }
    fn set_child(&mut self, c: u32, pa: u32, side: bool) {
        self.s[pa as usize].c[side as usize] = c;
    }
    // y is the parent of x
    // Will update y.scnt
    // Dirty: self.root, x.scnt, x <-> to
    fn __rotate_up(&mut self, x: u32, y: u32, side_x: bool) {
        let w = self.s[x as usize].c[!side_x as usize];
        self.set_child(w, y, side_x);
        self.set_child(y, x, !side_x);
        self.push_up(y);
    }

    // Nodes in path will be updated
    // Dirty: x.scnt, x <-> path[0]
    fn __splay(&mut self, x: u32, path: &[(u32, bool)]) {
        let mut n = path.len();
        while n != 0 {
            n -= 1;
            let (y, side_x) = path[n];
            if n == 0 {
                self.__rotate_up(x, y, side_x);
                break;
            }
            n -= 1;
            let (z, side_y) = path[n];
            if side_x == side_y {
                self.__rotate_up(y, z, side_y);
                self.__rotate_up(x, y, side_x);
            } else {
                self.__rotate_up(x, y, side_x);
                self.__rotate_up(x, z, side_y);
            }
        }
    }
    // Nodes from x to path[0] will be updated
    // Dirty: x <-> path[0]
    fn splay(&mut self, x: u32, path: &[(u32, bool)]) {
        self.__splay(x, path);
        self.push_up(x);
    }
    fn rotate_to_root(&mut self, x: u32, path: &[(u32, bool)]) {
        self.splay(x, path);
        self.root = x;
    }

    fn size(&self) -> u32 {
        // if self.root == 0 {
        //     return 0;
        // } else {
        return self.s[self.root as usize].scnt;
        // }
    }
    // The new node will be the root
    fn insert(&mut self, key: T) {
        if self.root == 0 {
            self.s.push(SplayNode::new(key));
            self.root = (self.s.len() - 1) as u32;
            return;
        }
        let mut cur = self.root;
        let mut path = Vec::new();
        loop {
            if self.s[cur as usize].key == key {
                self.s[cur as usize].cnt += 1;
                // cur.scnt will be updated by subsequent rotate_to_root
                break;
            }
            let side = self.s[cur as usize].key < key;
            path.push((cur, side));
            cur = self.s[cur as usize].c[side as usize];
            if cur == 0 {
                self.s.push(SplayNode::new(key));
                cur = (self.s.len() - 1) as u32;
                // cur <-> prev, cur.scnt and prev.scnt will be updated by
                // subsequent rotate_to_root
                break;
            }
        }
        self.rotate_to_root(cur, path);
    }
    // The target node will be the root
    // fn find(&mut self, key: &T) -> u32 {
    //     let mut cur = self.root;
    //     while cur != 0 && self.s[cur as usize].key != *key {
    //         let side = self.s[cur as usize].key < *key;
    //         cur = self.s[cur as usize].c[side as usize];
    //     }
    //     self.rotate_to_root(cur);
    //     return cur;
    // }
    // Find the first node whose value >= key
    // If found, then the node will be the root and returned.
    // Otherwise (all nodes < key), return 0
    fn lower_bound(&mut self, key: &T) -> u32 {
        let mut cur = self.root;
        let mut path = Vec::new();
        let mut ans_depth = 0;
        while cur != 0 {
            let side = self.s[cur as usize].key < *key;
            path.push((cur, side));
            if side {
                cur = self.rc(cur);
            } else {
                ans_depth = path.len();
                cur = self.lc(cur);
            }
        }
        let (prev, _) = match path.pop() {
            Some(prev) => prev,
            None => return 0,
        };
        let ans = if ans_depth <= path.len() {
            // prev != ans
            self.splay(prev, &path[ans_depth..path.len()]);
            path.truncate(ans_depth);
            let (ans, side) = match path.pop() {
                Some(ans) => ans,
                None => {
                    self.root = prev;
                    return 0;
                }
            };
            self.set_child(prev, ans, side);
            // ans.scnt will be updated by rotate_to_root later.
            ans
        } else {
            // prev is ans
            prev
        };
        self.rotate_to_root(ans, &path);
        return ans;
    }
    // The target node will be the root
    fn query_kth(&mut self, mut k: u32) -> u32 {
        let mut cur = self.root;
        let mut path = Vec::new();
        while cur != 0 {
            let lscnt = self.s[self.lc(cur) as usize].scnt;
            let cur_cnt = self.s[cur as usize].cnt;
            if lscnt < k && lscnt + cur_cnt >= k {
                self.rotate_to_root(cur, &path);
                return cur;
            }
            let side = lscnt < k;
            path.push((cur, side));
            if side {
                k -= lscnt + cur_cnt;
                cur = self.rc(cur);
            } else {
                cur = self.lc(cur);
            };
        }
        unreachable!();
    }
    // The remaining smallest will be the root.
    fn del_smaller(&mut self, key: &T) -> u32 {
        let rt = self.lower_bound(key);
        if rt == 0 {
            // if self.root == 0 {
            //     return 0;
            // }
            let deleted = self.s[self.root as usize].scnt;
            self.root = 0;
            return deleted;
        }
        // if self.lc(rt) == 0 {
        //     return 0;
        // }
        let deleted = self.s[self.lc(rt) as usize].scnt;
        self.s[rt as usize].c[0] = 0;
        self.push_up(rt);
        return deleted;
    }

    fn check_sanity_subtree(&self, rt: u32) {
        let mut scnt = self.s[rt as usize].cnt;
        if self.lc(rt) != 0 {
            scnt += self.s[self.lc(rt) as usize].scnt;
            self.check_sanity_subtree(self.lc(rt));
        }
        if self.rc(rt) != 0 {
            scnt += self.s[self.rc(rt) as usize].scnt;
            self.check_sanity_subtree(self.rc(rt));
        }
        assert_eq!(scnt, self.s[rt as usize].scnt);
    }
    #[allow(unused)]
    fn check_sanity(&self) {
        assert!(self.s[0] == SplayNode::<T>::default());
        if self.root == 0 {
            return;
        }
        self.check_sanity_subtree(self.root);
    }
}

impl<T: std::default::Default + std::cmp::Ord + std::fmt::Display> Splay<T> {
    fn __print_subtree(&self, rt: u32, str: &mut String) {
        let ori_len = str.len();
        if rt == 0 {
            println!("/\\");
            return;
        }
        let node = if self.s[rt as usize].cnt == 1 {
            format!("{}", self.s[rt as usize].key)
        } else {
            format!("{}*{}", self.s[rt as usize].key, self.s[rt as usize].cnt)
        };
        let len = node.len();
        print!("{}", node);
        print!("---");
        // str.push_str(&String::from_iter(std::iter::repeat(' ').take(len)));
        str.push_str(&std::iter::repeat(' ').take(len).collect::<String>());
        str.push_str(" | ");
        self.__print_subtree(self.lc(rt), str);
        println!("{}", str);
        let len = str.len();
        unsafe {
            str.as_bytes_mut()[len - 1] = b'-';
            str.as_bytes_mut()[len - 2] = b'-';
        }
        print!("{}", str);

        unsafe {
            str.as_bytes_mut()[len - 1] = b' ';
            str.as_bytes_mut()[len - 2] = b' ';
        }
        self.__print_subtree(self.rc(rt), str);

        str.truncate(ori_len);
    }
    fn print_subtree(&self, rt: u32) {
        self.__print_subtree(rt, &mut String::new());
    }
    #[allow(unused)]
    fn print_tree(&self) {
        self.print_subtree(self.root);
    }
}

