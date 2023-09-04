

#include "base/TreeNode.hpp"
// Definition for a Node.
class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
public:
    void run(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        Node dummy(-1);      /// 像链表的头节点
        Node *tail = &dummy; /// 像链表的滑动指针

        // 遍历root这一层，建立下一层的next连接
        while (root != nullptr)
        {
            // 尾插法，依次加入左右节点
            if (root->left != nullptr)
            {
                tail->next = root->left;
                tail = tail->next;
            }

            if (root->right != nullptr)
            {
                tail->next = root->right;
                tail = tail->next;
            }

            root = root->next;
        }

        connect(dummy.next);
    }

void run2(Node *root)
{
    while (root)
    {
        Node *next = nullptr; // the first node of next level
        Node *prev = nullptr; // previous node on the same level
        for (; root; root = root->next)
        {
            if (!next)
            {
                next = root->left ? root->left : root->right;
            }
            if (root->left)
            {
                if (prev)
                {
                    prev->next = root->left;
                }
                prev = root->left;
            }
            if (root->right)
            {
                if (prev)
                {
                    prev->next = root->right;
                }
                prev = root->right;
            }
        }
        root = next; // turn to next level
    }
}
    Node *connect(Node *root)
    {
        run2(root);
        return root;
    }
};