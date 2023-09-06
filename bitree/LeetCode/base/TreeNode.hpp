//
// Created by lianqing on 2023/8/18.
//
#ifndef OBJECT_TREENODE_H
#define OBJECT_TREENODE_H
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;
#define NONE -1 // 用这个代指空节点
#define print(x) cout << (x) << " "
#define NEXTLINE cout << endl
class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(): val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
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
TreeNode* creatTree(vector<int>& level_traversal) {
	if (level_traversal.empty()) {
		return nullptr;
	}
	reverse(level_traversal); // 利用popback作为尾队列
	TreeNode* root = mkNode(level_traversal);
	return root;
}
void printVector(const vector<int>& vec) {
	for (const auto& x: vec) {
		print(x);
	}
	NEXTLINE;
}
/**
 * 弹出左边路径中已经访问的点，并更新中序遍历的指针，最后返回当前路径的最后一个节点
 *
 * @param stk the path of the current traversal，注意栈顶节点是 当前节点的上一个节点
 * @param inorder a vector of integers representing the inorder traversal of the binary tree
 * @param oi an integer representing the index of the current TreeNode in the inorder traversal
 *
 * @return the last path node
 *
 */
TreeNode* goBack(stack<TreeNode*>& stk, const vector<int>& inorder, int& oi) {
	TreeNode* last_pop = nullptr;
	while (!stk.empty() && stk.top()->val == inorder[oi]) {
		last_pop = stk.top(); // 细微，栈顶保存着当前路径的前一个节点
		stk.pop();
		oi++;
	}
	return last_pop; // 最后一个被弹出的节点还有用，是转换到右子树的根节点
} // 函数足够短，细节清晰明白，没有犯错的空间
TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
	if (inorder.empty() || preorder.empty())
		return nullptr;
	TreeNode* root = new TreeNode(preorder[0]);
	stack<TreeNode*> pre_stk;
	pre_stk.push(root);
	int oi = 0;
	for (int pi = 1; pi < preorder.size(); ++pi) {
		TreeNode* curr = pre_stk.top(); // 回到原点，保证栈顶保存着当前路径的最后一个节点
		if (curr->val != inorder[oi]) {
			curr->left = new TreeNode(preorder[pi]);
			pre_stk.push(curr->left);
		}
		else {
			curr = goBack(pre_stk, inorder, oi);
			curr->right = new TreeNode(preorder[pi]);
			pre_stk.push(curr->right); // 一句保持一个完整的语义
		}
	}
	return root;
} // 就是怕你每一行执行完，你不能清晰明白的了解到发生了什么
#endif // OBJECT_TREENODE_H
