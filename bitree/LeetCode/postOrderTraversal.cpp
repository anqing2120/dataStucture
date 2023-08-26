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


// Morris 
int getRightConner(const TreeNode* current, TreeNode*& right_corner)
{// 左孩子存在时，找到最右下角的指针
	int ret = -1; // 未知错误
	right_corner = current->left;
	do
	{
		// 看一下下一步是不是终点，要不要结束
		if (right_corner->right == nullptr)
		{
			ret = 0;
			break; // 找到了最右下的指针
		}
		if (right_corner->right == current)
		{
			ret = 1;
			break; // 左子树遍历结束
		}
		// 进来循环之后先判断前提条件，然后执行逻辑

		right_corner = right_corner->right;
	} while (true);
	return ret;
}

vector<int> postOrderTraversal1(TreeNode* root)
{
	vector<int> result;
	TreeNode* cur(root); // 当前节点指针
	TreeNode* right_corner(nullptr); //左子树的右下角
	stack<TreeNode*> stack; // 用栈记录左子树的内容
	enum
	{
		firstRight, // 首次增加新的连接
		overLeft // 左子树遍历完成
	};

	while (cur != nullptr)
	{
		if (cur->left == nullptr) // 不存在左儿子，当前用完就可以丢掉了
		{
//			print("x");
//			print(cur->val); //6245
//			NEXTLINE;

			if(cur->right == nullptr){
				result.push_back(cur->val);
			}else{
				stack.push(cur);
			}

			cur = cur->right;
		}
		else
		{ // 有左儿子，用完当前还得回头，所以要留一条后路，就是找左儿子的右下角的右指针，指向当前当成后路
			int type = getRightConner(cur, right_corner);

			if (type == overLeft)
			{
				right_corner->right = nullptr; // 已经重复过，断开
//				print("y");
//				print(right_corner->val);
//				NEXTLINE;
				while(stack.empty()!=true){
					TreeNode* node = stack.top();
					if (node == cur) break;
					stack.pop();
					result.push_back(node->val);
				}
				cur = cur->right; //左边处理完成
			}
			else if (type == firstRight)
			{
				right_corner->right = cur; // 留个后门

//				print("z");
//				print(cur->val);
//				NEXTLINE;
				stack.push(cur); //
				cur = cur->left;
			}
			else
			{
				printf("something error.\n");
			}
		}
	}

	while(stack.empty()!=true){
		TreeNode* node = stack.top();stack.pop();
		result.push_back(node->val);
	}

	return result;
}





int main()
{
	vector<int> pre_tree{ 1, 2, 4, 8, -1, -1, -1,5,-1,9,-1,-1,3,6,-1,-1,7,-1,-1};
	TreeNode* root = creatTree(pre_tree);
	postOrder(root);
	NEXTLINE;

	vector<int> level = postOrderTraversal1(root);
	printVector(level);
}


