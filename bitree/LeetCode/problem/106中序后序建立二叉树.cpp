
#include "base/TreeNode.hpp"
class Solution
{
public:
    TreeNode *buildTreeHelper(vector<int> &inorder, int inStart, int inEnd,
                              vector<int> &postorder, int postStart, int postEnd)
    {
        if (inStart > inEnd || postStart > postEnd)
        {
            return nullptr;
        }

        int rootValue = postorder[postEnd];
        TreeNode *root = new TreeNode(rootValue);

        int rootIndex = inStart;
        while (inorder[rootIndex] != rootValue)
        {
            rootIndex++;
        }

        int leftSize = rootIndex - inStart;
        int rightSize = inEnd - rootIndex;

        root->left = buildTreeHelper(inorder, inStart, rootIndex - 1,
                                     postorder, postStart, postStart + leftSize - 1);
        root->right = buildTreeHelper(inorder, rootIndex + 1, inEnd,
                                      postorder, postStart + leftSize, postEnd - 1);

        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return buildTreeHelper(inorder, 0, inorder.size() - 1,
                               postorder, 0, postorder.size() - 1);
    }
};