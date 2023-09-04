#include "../base/TreeNode.hpp"

class Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        // check input
        if (preorder.empty() || inorder.empty())
        {
            return nullptr;
        }

        // declare data
        stack<TreeNode *> pre_stk; // 记录先序遍历的路径
        TreeNode *root = new TreeNode(preorder[0]);
        pre_stk.push(root);

        int inorderIndex = 0;
        // 用栈模拟先序遍历，中序遍历用于确认叶子节点
        for (int i = 1; i < preorder.size(); ++i)
        {
            TreeNode *cur = pre_stk.top();
            if (cur->val != inorder[inorderIndex]) // 不到叶子节点，向左下走一步
            {
                cur->left = new TreeNode(preorder[i]);
                pre_stk.push(cur->left); // 记录路径
            }
            else
            {
                // 当前是叶子节点 回退
                while (!pre_stk.empty() && pre_stk.top()->val == inorder[inorderIndex])
                {
                    cur = pre_stk.top();
                    pre_stk.pop();
                    ++inorderIndex; // 跳过已经访问过的左节点
                }
                cur->right = new TreeNode(preorder[i]); // 左边完成，转到右边
                pre_stk.push(cur->right);
            }
        }

        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &preorder)
    {
        if (preorder.empty() || inorder.empty())
        {
            return nullptr;
        }
        unordered_map<int, int> inorderV2idx;
        for (int i = 0; i < inorder.size(); i++)
        {
            inorderV2idx[inorder[i]] = i; // val --> idx
        }
        return buildTreeHelper(preorder, 0, preorder.size() - 1, inorderV2idx, 0, inorder.size() - 1);
    }

    TreeNode *buildTreeHelper(vector<int> &preorder, int preStart, int preEnd, unordered_map<int, int> &inorderV2idx, int inStart, int inEnd)
    {
        if (preStart > preEnd || inStart > inEnd)
        {
            return nullptr;
        }
        TreeNode *root = new TreeNode(preorder[preStart]);
        int rootIndex = inorderV2idx[root->val];
        int leftSubtreeSize = rootIndex - inStart;
        root->left = buildTreeHelper(preorder, preStart + 1, preStart + leftSubtreeSize, inorderV2idx, inStart, rootIndex - 1);
        root->right = buildTreeHelper(preorder, preStart + leftSubtreeSize + 1, preEnd, inorderV2idx, rootIndex + 1, inEnd);
        return root;
    }
};