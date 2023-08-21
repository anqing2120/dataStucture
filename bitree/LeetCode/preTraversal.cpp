//
// Created by lianqing on 2023/8/18.
//
#include <stack>
#include "TreeNode.h"


// 递归
void preOrder(TreeNode* root){
    if(nullptr!=root){
        print(root->val);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// 非递归的二叉树先序遍历1：找到最小重复单元

vector<int> preTraversal(TreeNode* root){
    vector<int> out_vec;
    do{
        if(nullptr == root){
            break;
        }

        stack<TreeNode*> path_ptr;
        TreeNode* ptr(root);
        do{
            // 从根开始 一路向左
            while(ptr){
                out_vec.push_back(ptr->val);
                path_ptr.push(ptr);
                ptr=ptr->left;
            }
            // 回退一步 切到右边 重新开始
            if (path_ptr.empty()) break;
            ptr = path_ptr.top();
            path_ptr.pop();
            ptr = ptr->right;

        }while(true);

    }while(false);
    return out_vec;
}


vector<int> preTraversal2(TreeNode* root) {
    vector<int> out_vec;
    do{
        if(nullptr == root){
            break;
        }

        stack<TreeNode*> path_ptr;
        TreeNode* ptr(root);
        path_ptr.push(ptr);

        // 最小重复单元是 访问根，先让右儿子入栈，再让左儿子入栈
        while(!path_ptr.empty()){
            ptr = path_ptr.top();
            out_vec.push_back(ptr->val);
            path_ptr.pop();

            // 反过来顺序 先右边后左边
            if(ptr->right){
                path_ptr.push(ptr->right);
            }
            if(ptr->left){
                path_ptr.push(ptr->left);
            }

        }

    }while(false);
    return out_vec;
}

int main(){
    vector<int> level{1,-1,2,3,-1,4,5};
    TreeNode* root = creatTree(level);
    level = preTraversal2(root);

    preOrder(root);NEXTLINE;

    for (auto x: level){
        print(x);
    }
    NEXTLINE;
}