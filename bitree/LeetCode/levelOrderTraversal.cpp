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

vector<int> levelOrderTraversal(TreeNode* root){
	vector<int> result;



	return result;
}

int main()
{
	vector<int> pre_tree{ 1, 2, 4, 8, -1, -1, -1,5,-1,9,-1,-1,3,6,-1,-1,7,-1,-1};
	TreeNode* root = creatTree(pre_tree);
	levelOrder(root);
	NEXTLINE;

	vector<int> level = levelOrderTraversal(root);
	printVector(level);
}