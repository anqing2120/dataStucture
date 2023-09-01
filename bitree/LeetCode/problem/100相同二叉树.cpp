
#include "../base/TreeNode.hpp"


class Solution {
public:
    bool isSameTree1(TreeNode* p, TreeNode* q) { // 等价于从栈顶取出值
        if (p == nullptr && q == nullptr) return true;
        if (p == nullptr || q == nullptr) return false; // 这里是前结束
        if (p->val != q->val) return false; // 这里是后结束
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right); // 压入下一次的数据
    }


    bool isSameTree(TreeNode* p, TreeNode* q) {
        stack<pair<TreeNode*, TreeNode*>> s;  //就像是函数的栈

        s.push(make_pair(p, q)); // 初始化栈

        while (!s.empty()) {  // 每次循化就是栈的内容的一次替换
            auto curr = s.top();
            s.pop();

            TreeNode* p = curr.first;
            TreeNode* q = curr.second; // 拿出当前栈的内容

            // 执行计算动作
            if (!p && !q) {
                continue;
            }

            if (!p || !q) {
                return false;
            }

            if (p->val != q->val) {
                return false;
            }
            
            // 放入下一次运算的内容
            s.push(make_pair(p->left, q->left));
            s.push(make_pair(p->right, q->right));
        }

        return true;
    }
};