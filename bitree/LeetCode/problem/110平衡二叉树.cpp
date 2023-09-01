#include "../base/TreeNode.hpp"


class Solution {
public:
    int height(TreeNode* root) {
       if(root == nullptr) return 0;
       return max(height(root->left), height(root->right)) + 1;
    }

    int height_stk(TreeNode* root) {
        // 层次遍历，速度慢于递归
        queue<TreeNode*> q;
        q.push(root);

        int height = 0;
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            ++height;
        }
        return height;
    }

    // 左右子树高度差不超过1，即平衡二叉树
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) return true;
        return abs(height_stk(root->left) - height_stk(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }



    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = getHeight(node->left);
        if (leftHeight == -1) {
            return -1;
        }

        int rightHeight = getHeight(node->right);
        if (rightHeight == -1) {
            return -1;
        }

        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        } // 把判断嵌入到递归，相当于剪枝操作

        return 1 + max(leftHeight, rightHeight);
    }
    bool isBalanced_quick(TreeNode* root) {
        return getHeight(root) == -1 ? false : true;
    }
};