//
// Created by lianqing on 2023/8/25.
//

#include "base/TreeNode.hpp"

void inOrder(TreeNode* root)
{
	if (root)
	{
		inOrder(root->left);
		print(root->val);
		inOrder(root->right);
	}
}
vector<int> inorderTraversal(TreeNode* root)
{
    vector<int> ans;
    if (root == nullptr) {
        return ans;
    }

    stack<TreeNode*> stk;
    TreeNode* ptr = root;

    while (ptr != nullptr || !stk.empty()) {
        while (ptr != nullptr) {
            stk.push(ptr);
            ptr = ptr->left;
        }
        TreeNode* father = stk.top();
        stk.pop();
        ans.push_back(father->val);
        ptr = father->right;
    }

    return ans;
}

// 简化后栈的写法 注意到栈里面上下节点的关系是 下面是父亲节点 上面是左孩子
vector<int> inorderTraversal1(TreeNode* root)
{
	vector<int> res;
	do
	{
		if (nullptr == root)
		{
			break;
		}
		stack<const TreeNode*> stk; // node cannot be changed
		const TreeNode* ptr(root); // pointer to now node

		while (!stk.empty() || nullptr != ptr)
		{
			if (nullptr != ptr)
			{ // pointer not null
				stk.push(ptr); // record the path
				ptr = ptr->left;// just go left
			}
			else
			{ // ptr is null
				// res.push_back(-1) means left node is null
				const TreeNode* father = stk.top(); // get father node
				stk.pop();
				res.push_back(father->val); // print father node
				ptr = father->right;// now change to right
			}
		}

	} while (false);

	return res;
}

vector<int> inorderMyStyle(TreeNode* root)
{
	vector<int> res;

	stack<const TreeNode*> path;
	const TreeNode* now_ptr = root;
	do
	{
		while (now_ptr != nullptr)
		{
			path.push(now_ptr);
			now_ptr = now_ptr->left;
		}
		// print(ptr:nullptr) 来到最左下的空
		if (path.empty())
		{
			break;
		}
		const TreeNode* father = path.top(); // get father node
		path.pop();

		res.push_back(father->val); // print father node
		now_ptr = father->right;// now change to right
	} while (true);
	return res;
}

// 中序遍历 3 ：Morris方法，不使用栈，空间复杂度O(1)
// 注意到 先 中 后 只是取value的位置不同，Morris方法遍历的流程是一样的
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

vector<int> inorderTraversal3(TreeNode* root)
{
	vector<int> result;
	TreeNode* cur(root); // 当前节点指针
	TreeNode* right_corner(nullptr); //左子树的右下角
	enum
	{
		firstRight, // 首次增加新的连接
		overLeft // 左子树遍历完成
	};

	while (cur != nullptr)
	{
		if (cur->left == nullptr) // 不存在左儿子，当前用完就可以丢掉了
		{
			result.push_back(cur->val);
			cur = cur->right;
		}
		else
		{ // 有左儿子，用完当前还得回头，所以要留一条后路，就是找左儿子的右下角的右指针，指向当前当成后路
			int type = getRightConner(cur, right_corner);

			if (type == overLeft)
			{
				right_corner->right = nullptr; // 已经重复过，断开
				result.push_back(cur->val);
				cur = cur->right; //左边处理完成
			}
			else if (type == firstRight)
			{
				right_corner->right = cur; // 留个后门
				cur = cur->left;
			}
			else
			{
				printf("something error.\n");
			}
		}
	}

	return result;
}

int main()
{
	vector<int> pre_tree{ 7, 6, -1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1 };
	TreeNode* root = creatTree(pre_tree);
	inOrder(root);
	NEXTLINE;

	vector<int> level = inorderTraversal3(root);
	printVector(level);
}