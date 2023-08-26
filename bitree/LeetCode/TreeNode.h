//
// Created by lianqing on 2023/8/18.
//

#ifndef OBJECT_TREENODE_H
#define OBJECT_TREENODE_H

#include <vector>
#include <algorithm>
#include <iostream>
using namespace  std;

#define NONE -1 // 用这个代指空节点
#define print(x) cout<<(x)<<" "
#define NEXTLINE cout<<endl



class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

};

TreeNode* mkNode(vector<int>&vec){
    TreeNode* ret = nullptr;
    do{
        if(vec.empty()){
            break;
        }

        int val = vec.back();
        vec.pop_back();
        if (NONE == val){
            break;
        }

        ret = new TreeNode(val);
        ret->left = mkNode(vec);
        ret->right = mkNode(vec);

    } while (false);
    return ret;
}

void reverse(vector<int>& vec){
    if(vec.empty()){
        return;
    }

    int front =-1;
    int end = vec.size();
    do{
        ++front;
        --end;
        if(front<end){
            swap(vec[front],vec[end]);
        }else{
            break;
        }
    }while(true);
}


TreeNode* creatTree(vector<int> &level_traversal){
    if(level_traversal.empty()){
        return nullptr;
    }
    reverse(level_traversal); // 利用popback作为尾队列
    TreeNode* root= mkNode(level_traversal);
    return root;
}

void printVector(vector<int> & vec){
	for (auto x : vec)
	{
		print(x);
	}
	NEXTLINE;
}


#endif //OBJECT_TREENODE_H
