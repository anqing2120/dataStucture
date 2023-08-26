//
// Created by lianqing on 2023/8/26.
//
#include <stack>
#include "TreeNode.h"


void postOrder(TreeNode* root){
	if(root){
		postOrder(root->left);
		postOrder(root->right);
		print(root->val);
	}
}

vector<int> postOrderTraversal(TreeNode* root){
	vector<int> result;

	do
	{
		const TreeNode* now = root;
		const TreeNode* prev_son = nullptr;
		stack<const TreeNode*> path;

		if (nullptr == root)
		{
			break;
		}

		bool go_back = false;

		do
		{
			while (now)
			{
				path.push(now);
				now = now->left;
			}
			//print(now->val);
			if (path.empty())
			{
				break;
			}
			const TreeNode* father = path.top();
			if (prev_son != father->right)
			{ // 跳过重复
				now = father->right;
			}
			if (now == nullptr) // 左右儿子都是空，或者左右都访问过了
			{
				result.push_back(father->val);
				path.pop();
				prev_son = father;
			}
		} while (true);

	}while(false);

	return result;
}

int main()
{
	vector<int> pre_tree{ 7, 6, -1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1 };
	TreeNode* root = creatTree(pre_tree);
	postOrder(root);
	NEXTLINE;

	vector<int> level = postOrderTraversal(root);
	printVector(level);
}


