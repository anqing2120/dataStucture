//
// Created by lianqing on 2023/8/25.
//


#include <stack>
#include "TreeNode.h"

void inOrder(TreeNode* root){
	if(root){
		inOrder(root->left);
		print(root->val);
		inOrder(root->right);
	}
}



void setNullLeft(stack<TreeNode*> &stk){
	if (stk.empty()){
		return;
	}
	TreeNode* root = stk.top();
	stk.pop();
	root->left = nullptr;
	stk.push(root);
}

vector<int> inorderTraversal(TreeNode* root){
	stack<TreeNode*> stk;
	vector<int> ans;

	do{
		if(nullptr == root){
			break;
		}
		stk.push(root);
		TreeNode* ptr=nullptr;

		do{
			if(stk.empty()){
				break;
			}
			ptr = stk.top();
			while(ptr->left){
				stk.push(ptr->left);
				ptr = ptr->left;
			}
			// ptr->left is null ; print(left)
			ans.push_back(ptr->val); // print(root)
			stk.pop();
			setNullLeft(stk); // 弹出后，断开与父节点的联系
			if(ptr->right){
				stk.push(ptr->right);
			}

		}while(true);
	}while(false);

	return ans;
}

int main()
{
	vector<int> level{ 1, 2, 3, 4 };
	TreeNode* root = creatTree(level);
	inOrder(root);
	NEXTLINE;

	level = inorderTraversal(root);
	for (auto x : level)
	{
		print(x);
	}
	NEXTLINE;
}