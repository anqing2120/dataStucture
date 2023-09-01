#include "../base/TreeNode.hpp"


class Solution {
public:

    // 轴对称， 我的左子树和你的右子树相同
    bool isMirror(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right == nullptr) return true;
        if (left == nullptr || right == nullptr) return false;
        if (left->val != right->val) return false;
        return isMirror(left->left, right->right) && isMirror(left->right, right->left);
    }

    bool isMirror_2(TreeNode* left, TreeNode* right) {
        queue<pair<TreeNode*, TreeNode*>> q;
        q.push({left, right});

        while(!q.empty()) {
            auto [l, r] = q.front();
            q.pop();

            if (l == nullptr && r == nullptr) continue; // 同时为空相等
            if (l == nullptr || r == nullptr) return false;//一个空一个不空
            if (l->val != r->val) return false; // 同时不为空
            q.push({l->left, r->right});
            q.push({l->right, r->left});
        }
        return true;
    }


    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return isMirror_2(root->left, root->right);
    }
};