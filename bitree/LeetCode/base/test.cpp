//
// Created by lianqing on 2023/8/18.
//

#include "TreeNode.hpp"

void preOrder(TreeNode* root){
    if(nullptr!=root){
        print(root->val);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void test(){
    vector<int> level_tree{7,6,-1,2,-1,-1,3,4,-1,-1,5,-1,-1};
    TreeNode* root = creatTree(level_tree);
    preOrder(root);

    NEXTLINE;
}

int main(){

    test();
    return 0;
}