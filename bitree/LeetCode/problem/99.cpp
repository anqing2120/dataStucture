/*
    题意：二叉搜索树，有两个节点的值被交换了。请你恢复二叉搜索树。
*/


#include "../base/TreeNode.hpp"

class Solution {
public:

    // 特点就是每次都是从根节点走到最左下的空节点，并记录路径
    vector<TreeNode*> getInorderList(TreeNode* root){
        vector<TreeNode*> inorder_list; // 保存中序遍历
        if(root == nullptr) return inorder_list; // 空树
        stack<TreeNode*> stk;// 保存走过的路径
        TreeNode* ptr = root;// 从根开始
        while (ptr != nullptr || !stk.empty()){ // 没到叶子节点 或者栈空
            while (ptr != nullptr){ // 没到叶子节点
                stk.push(ptr); // 记录路径
                ptr = ptr->left; // 一直向左走
            }
            // 走到最左边的空节点，回退一步
            TreeNode* father = stk.top();
            stk.pop();
            inorder_list.push_back(father); // 记录根节点
            ptr = father->right; //左边已经遍历，向右走
        }
        return inorder_list;
    }

    // Morris 中序遍历
    // 向着左下移动，每一步都要先建立好后门，先联系再断开
    // 像右下移动，秩序移动即可
    // 需要注意的一点是如果联系已经存在，则需要断开，且表明左子树处理结束
    vector<TreeNode*> getInorderList2(TreeNode* root){
        vector<TreeNode*> inorder_list; // 保存中序遍历的结果
        TreeNode* cur = root; // 从根节点开始

        while(cur != nullptr){ // 没到叶子节点
            if(cur->left == nullptr){ // 没有左儿子，记录之后，移动到右儿子
                inorder_list.push_back(cur);
                cur = cur->right;
            }else{
                TreeNode* pre = cur->left; // 存在左儿子
                while(pre->right){ // 找到左子树的最右节点
                    if(pre->right == cur){ // 连接已经存在
                        break;
                    }
                    pre = pre->right;
                }
                if(pre->right == nullptr){ // 没有右儿子
                    pre->right = cur; // 留一条后门到当前节点
                    cur = cur->left; // 往下走到左儿子
                }else{
                    pre->right = nullptr; // 已经连接 ,断开
                    inorder_list.push_back(cur); // 左边完成遍历，根节点记录
                    cur = cur->right; // 往下走到右儿子
                }
            }
        }
        return inorder_list;
    }

void recoverTree_morris(TreeNode* &root) {
    if (root == nullptr) return; // 空树

    TreeNode* prev = nullptr; // 保存前驱
    TreeNode* first = nullptr; // 保存第一个逆序节点
    TreeNode* second = nullptr; // 保存第二个逆序节点

    TreeNode* cur = root; // 从根节点开始
    while (cur != nullptr) {
        if (cur->left == nullptr) { // 没有左儿子
            if (prev && cur->val < prev->val) {
                if (first == nullptr) { // 第一个逆序节点
                    first = prev;
                }
                second = cur;
            }
            prev = cur; // 记录前驱
            cur = cur->right; // 往右下走
        } else {
            TreeNode* pre = cur->left; // 找到左孩子的最右儿子
            while (pre->right && pre->right != cur) {
                pre = pre->right; 
            }

            if (pre->right == nullptr) { // 还没有建立连接
                pre->right = cur; // 记录当前后门
                cur = cur->left; // 往左下走
            } else {
                pre->right = nullptr; // 已经建立连接，断开
                
                if (prev && cur->val < prev->val) {
                    if (first == nullptr) {
                        first = prev;
                    } else {
                        second = cur;
                        break;
                    }
                }
                // 左子树处理完成
                prev = cur;
                cur = cur->right;
            }
        }
    }

    if (first && second) {
        swap(first->val, second->val);
    }
}

    // 中序遍历 得到指针序列 从左到右 和 从右到左 找到第一个逆序节点 交换
    void recoverTree(TreeNode* &root) {
        if(root == nullptr) return;
        vector<TreeNode*> inorder_list = getInorderList2(root);
        int size = inorder_list.size();
        int l = 0;
        int r = size - 1;

        while(l<r && inorder_list.at(l)->val < inorder_list.at(l+1)->val) ++l;
        while(l<r && inorder_list.at(r)->val > inorder_list.at(r-1)->val) --r;

        if (l < r) {
            int tmp = inorder_list.at(l)->val;
            inorder_list.at(l)->val = inorder_list.at(r)->val;
            inorder_list.at(r)->val = tmp;
        }
    }


    void inOrder(TreeNode* root){
        if(root == nullptr) return;
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }


};

void test(){
    Solution sol;
    vector<int> pre_tree{ 31, 47, 14, 8, -1, -1, -1,25,-1,29,-1,-1,43,36,-1,-1,22,-1,-1};
    TreeNode* root = creatTree(pre_tree);
    sol.inOrder(root);
    NEXTLINE;

    sol.recoverTree_morris(root);

    sol.inOrder(root);
    NEXTLINE;
}


int main()
{
    test();
    return 0;
}