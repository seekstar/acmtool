/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    unordered_map<int, int> in_pos;
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0) {
            return NULL;
        }
        for (int i = 0; i < inorder.size(); ++i) {
            in_pos[inorder[i]] = i;
        }
        int rt_post_index = postorder.size() - 1;
        return dfs(postorder, 0, postorder.size(), rt_post_index);
    }
private:
    TreeNode* dfs(const vector<int>& postorder, int in_begin_pos, int in_end_pos, int &rt_post_index) {
        int rt_val = postorder[rt_post_index];
        int rt_in_pos = in_pos[rt_val];
        TreeNode *rt = new TreeNode(rt_val);
        if (rt_in_pos + 1 < in_end_pos) {
            rt->right = dfs(postorder, rt_in_pos + 1, in_end_pos, --rt_post_index);
        }
        if (in_begin_pos < rt_in_pos) {
            rt->left = dfs(postorder, in_begin_pos, rt_in_pos, --rt_post_index);
        }
        return rt;
    }
};
