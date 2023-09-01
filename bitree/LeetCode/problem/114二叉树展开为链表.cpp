// 给你二叉树的根结点 root ，请你将它展开为一个单链表：

// 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
// 展开后的单链表应该与二叉树 先序遍历 顺序相同。

#include "../base/TreeNode.hpp"

class Solution {
public:
    void flatten_1(TreeNode* root) {
        if (!root) return;
        flatten(root->left);
        flatten(root->right);
        TreeNode* tmp_r = root->right;// 先联
        root->right = root->left; // 再断开
        root->left = nullptr; //左边赋值为空
        TreeNode* q = root;
        while (q->right) q = q->right; // 走到末尾
        q->right = tmp_r; // 连接
    }

    void flatten(TreeNode* root) {
        if (root == nullptr) return;

        stack<TreeNode*> stk;
        TreeNode *ptr = root;
        TreeNode *pre = nullptr;

        while (ptr != nullptr || !stk.empty()) { // 这里是个关键的地方，栈空不是唯一条件
            if (ptr == nullptr) {
                ptr = stk.top();
                stk.pop();
                if (pre) {
                    pre->right = ptr;
                }
            } else {
                if (ptr->left != nullptr) {
                    if (ptr->right) {
                        stk.push(ptr->right);
                    }
                    ptr->right = ptr->left;
                    ptr->left = nullptr;
                }
                pre = ptr;
                ptr = ptr->right;
            }
        }
    }
};