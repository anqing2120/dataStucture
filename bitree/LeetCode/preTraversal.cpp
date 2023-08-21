//
// Created by lianqing on 2023/8/18.
//
#include <stack>
#include "TreeNode.h"

// 递归
void preOrder(TreeNode* root)
{
	if (nullptr != root)
	{
		print(root->val);
		preOrder(root->left);
		preOrder(root->right);
	}
}

// 非递归的二叉树先序遍历1：找到最小重复单元
vector<int> preTraversal(TreeNode* root)
{
	vector<int> out_vec;
	do
	{
		if (nullptr == root)
		{
			break;
		}

		stack<TreeNode*> path_ptr;
		TreeNode* ptr(root);
		do
		{
			// 从根开始 一路向左
			while (ptr)
			{
				out_vec.push_back(ptr->val);
				path_ptr.push(ptr);
				ptr = ptr->left;
			}
			// 回退一步 切到右边 重新开始
			if (path_ptr.empty())
				break;
			ptr = path_ptr.top();
			path_ptr.pop();
			ptr = ptr->right;

		} while (true);

	} while (false);
	return out_vec;
}

vector<int> preTraversal2(TreeNode* root)
{
	vector<int> out_vec;
	do
	{
		if (nullptr == root)
		{
			break;
		}

		stack<TreeNode*> path_ptr;
		TreeNode* ptr(root);
		path_ptr.push(ptr);

		// 最小重复单元是 访问根，先让右儿子入栈，再让左儿子入栈
		while (!path_ptr.empty())
		{
			ptr = path_ptr.top();
			out_vec.push_back(ptr->val);
			path_ptr.pop();

			// 反过来顺序 先右边后左边
			if (ptr->right)
			{
				path_ptr.push(ptr->right);
			}
			if (ptr->left)
			{
				path_ptr.push(ptr->left);
			}

		}

	} while (false);
	return out_vec;
}

// 先序遍历 3 ：Morris方法，不使用栈，空间复杂度O(1)

int getRightConner(TreeNode* current,TreeNode* &right_corner)
{// 左孩子存在时，找到最右下角的指针
	int ret = -1; // 未知错误
	right_corner = current->left;
	do
	{
		// 看一下下一步是不是终点，要不要结束
		if (right_corner->right == nullptr){
			ret = 0;
			break; // 找到了最右下的指针
		}
		if (right_corner->right == current) {
			ret = 1;
			break; // 左子树遍历结束
		}
		right_corner = right_corner->right;
	} while (true);
	return ret;
}

vector<int> preTraversal3(TreeNode* root)
{
	vector<int> result;
	TreeNode* cur = root; // 当前节点指针
	TreeNode* prev = nullptr; // 前驱节点指针
	TreeNode* right_corner=nullptr; //左子树的右下角
	enum {
		firstRight, // 首次增加新的连接
		overLeft // 左子树遍历完成
	};

	while (cur != nullptr)
	{
		if (cur->left == nullptr) // 不存在左儿子，当前用完就可以丢掉了
		{
			result.push_back(cur->val);
			prev = cur;
			cur = cur->right;
		}
		else
		{ // 有左儿子，用完当前还得回头，所以要留一条后路，就是找左儿子的右下角的右指针，指向当前当成后路
			int type = getRightConner(cur,right_corner);

			if (type == overLeft)
			{
				right_corner->right = nullptr; // 已经重复过，断开
				cur = cur->right; //左边处理完成
			}
			else if(type == firstRight)
			{
				right_corner->right = cur; // 留个后门

				result.push_back(cur->val);
				prev = cur;
				cur = cur->left;
			}else{
				printf("something error.\n");
			}
		}
	}

	return result;
}

int main()
{
	vector<int> level{ 34, 32, -1, 31, 4, 25, 64, 7, 82, 9 };
	TreeNode* root = creatTree(level);
	level = preTraversal3(root);

	preOrder(root);
	NEXTLINE;

	for (auto x : level)
	{
		print(x);
	}
	NEXTLINE;
}