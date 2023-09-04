//
// Created by lianqing on 2023/8/18.
//

#ifndef OBJECT_TREENODE_H
#define OBJECT_TREENODE_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace  std;


#define NONE -1 // 用这个代指空节点
#define print(x) cout<<(x)<<" "
#define NEXTLINE cout<<endl



class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

TreeNode* mkNode(vector<int>& vec) {
    if (vec.empty()) {
        return nullptr;
    }
    
    int val = vec.back();
    vec.pop_back();
    
    if (val == NONE) {
        return nullptr;
    }
    
    TreeNode* ret = new TreeNode(val);
    ret->left = mkNode(vec);
    ret->right = mkNode(vec);
    
    return ret;
}

void reverse(vector<int>& vec) {
    int front = 0;
    int end = vec.size() - 1;
    while (front < end) {
        swap(vec[front], vec[end]);
        ++front;
        --end;
    }
}

TreeNode* creatTree(vector<int> &level_traversal){
    if(level_traversal.empty()){
        return nullptr;
    }
    reverse(level_traversal); // 利用popback作为尾队列
    TreeNode* root= mkNode(level_traversal);
    return root;
}

void printVector(const vector<int>& vec) {
    for (const auto& x : vec) {
        print(x);
    }
    NEXTLINE;
}


#endif //OBJECT_TREENODE_H
