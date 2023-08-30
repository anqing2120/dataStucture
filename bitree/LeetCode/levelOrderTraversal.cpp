//
// Created by lianqing on 2023/8/26.
//

#include<queue>
#include "TreeNode.h"

void levelOrder(TreeNode* root){
	queue<TreeNode*> que;
	que.push(root);
	do{
		if (que.empty()){
			break;
		}

		TreeNode* current = que.front();que.pop();
		print(current->val);
		if (current->left){
			que.push(current->left);
		}
		if(current->right){
			que.push(current->right);
		}

	}while(true);

}

// 递归方法
void traverse(TreeNode* root, int level, vector<vector<int> >& vec){
	if (root == nullptr){
		return;
	}
	// 确认当前层的 袋子 存在
	if (vec.size() < level){
		vec.push_back(vector<int>());
	}

	// 添加当前节点 level-1 对应第level层的袋子
	vec[level-1].push_back(root->val);
	traverse(root->left, level+1, vec);
	traverse(root->right, level+1, vec);
}

vector<vector<int> > levelOrderTraversal(TreeNode* root){
	vector<vector<int> > vec_level;
	traverse(root,1,vec_level);
	return vec_level;
}

int main()
{
	vector<int> pre_tree{ 1, 2, 4, 8, -1, -1, -1,5,-1,9,-1,-1,3,6,-1,-1,7,-1,-1};
	TreeNode* root = creatTree(pre_tree);
	levelOrder(root);
	NEXTLINE;

	vector<vector<int> > levels = levelOrderTraversal(root);
	for(auto &vec:levels){
		printVector(vec);
	}
}