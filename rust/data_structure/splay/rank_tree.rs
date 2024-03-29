#[derive(Clone)]
struct SplayNode<T> {
    c: [u32; 2],
    pa: u32,
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
            pa: 0,
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
            pa: 0,
            cnt: 1,
            scnt: 1,
            key: key,
        }
    }
}

struct Splay<T> {
    // Dirty: s[0].pa
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
    fn side(&self, rt: u32) -> bool {
        return rt == self.rc(self.s[rt as usize].pa);
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
        self.s[c as usize].pa = pa;
    }
    // y is the parent of x
    // Will update y.scnt
    // Dirty: self.root, x.scnt, x <-> y.pa
    fn __rotate_up(&mut self, x: u32, y: u32, side_x: bool) {
        let w = self.s[x as usize].c[!side_x as usize];
        self.set_child(w, y, side_x);
        self.set_child(y, x, !side_x);
        self.push_up(y);
    }

    // Nodes from x to root will be updated
    // Dirty: x <-> to
    fn __splay(&mut self, x: u32, to: u32) {
        if x == 0 {
            return;
        }
        let mut y = self.s[x as usize].pa;
        let mut side_x = self.side(x);
        while y != to {
            let z = self.s[y as usize].pa;
            if z == to {
                self.__rotate_up(x, y, side_x);
                break;
            }
            let z_pa = self.s[z as usize].pa;
            let side_y = self.side(y);
            let side_z = self.side(z);
            if side_x == side_y {
                self.__rotate_up(y, z, side_y);
                self.__rotate_up(x, y, side_x);
            } else {
                self.__rotate_up(x, y, side_x);
                self.__rotate_up(x, z, side_y);
            }
            side_x = side_z;
            y = z_pa;
        }
        self.push_up(x);
    }
    // Nodes from cur to root will be updated
    fn rotate_to_root(&mut self, cur: u32) {
        if cur == 0 {
            return;
        }
        self.__splay(cur, 0);
        self.root = cur;
        self.s[cur as usize].pa = 0;
    }
    fn rotate_to(&mut self, x: u32, to: u32, side: bool) {
        if to == 0 {
            self.rotate_to_root(x);
        } else {
            self.__splay(x, to);
            self.set_child(x, to, side);
        }
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
        let mut pa = 0; // Actually no need to initialize.
        let mut side = false; // Actually no need to initialize.
        loop {
            if cur == 0 {
                self.s.push(SplayNode::new(key));
                cur = (self.s.len() - 1) as u32;
                self.set_child(cur, pa, side);
                // cur.scnt and pa.scnt will be updated by subsequent
                // rotate_to_root
                break;
            } else if self.s[cur as usize].key == key {
                self.s[cur as usize].cnt += 1;
                // cur.scnt will be updated by subsequent rotate_to_root
                break;
            }
            pa = cur;
            side = self.s[cur as usize].key < key;
            cur = self.s[cur as usize].c[side as usize];
        }
        self.rotate_to_root(cur);
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
        let mut prev = 0;
        let mut ans = 0;
        while cur != 0 {
            prev = cur;
            if self.s[cur as usize].key < *key {
                cur = self.rc(cur);
            } else {
                ans = cur;
                cur = self.lc(cur);
            }
        }
        if prev != ans {
            self.rotate_to(prev, ans, false);
        }
        self.rotate_to_root(ans);
        return ans;
    }
    // The target node will be the root
    fn query_kth(&mut self, mut k: u32) -> u32 {
        let mut cur = self.root;
        while cur != 0 {
            let lscnt = self.s[self.lc(cur) as usize].scnt;
            let cur_cnt = self.s[cur as usize].cnt;
            if lscnt < k {
                if lscnt + cur_cnt >= k {
                    self.rotate_to_root(cur);
                    return cur;
                }
                k -= lscnt + cur_cnt;
                cur = self.rc(cur);
            } else {
                cur = self.lc(cur);
            }
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
            assert_eq!(self.s[self.lc(rt) as usize].pa, rt);
            scnt += self.s[self.lc(rt) as usize].scnt;
            self.check_sanity_subtree(self.lc(rt));
        }
        if self.rc(rt) != 0 {
            assert_eq!(self.s[self.rc(rt) as usize].pa, rt);
            scnt += self.s[self.rc(rt) as usize].scnt;
            self.check_sanity_subtree(self.rc(rt));
        }
        assert_eq!(scnt, self.s[rt as usize].scnt);
    }
    #[allow(unused)]
    fn check_sanity(&self) {
        // assert!(self.s[0] == SplayNode::<T>::default());
        assert_eq!(self.s[0].c[0], 0);
        assert_eq!(self.s[0].c[1], 0);
        // assert_eq!(self.s[0].pa, 0);
        assert_eq!(self.s[0].cnt, 0);
        assert_eq!(self.s[0].scnt, 0);
        assert!(self.s[0].key == T::default());
        if self.root == 0 {
            return;
        }
        assert_eq!(self.s[self.root as usize].pa, 0);
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

