#include "../base/TreeNode.hpp"
class Solution {
public:
	bool isLeaf(TreeNode* root) const {
		if (root == nullptr) {
			return false;
		}
		return root->left == nullptr && root->right == nullptr;
	}
	// 是否存在路径之和等于目标值
	bool hasPathSum(TreeNode* root, int targetSum) {
		// 函数的参数就是当前步骤的状态码 root记录当前节点 targetSum记录剩余值
		if (root == nullptr) {
			return false;
		}
		if (root->val == targetSum) {
			// 相等同时确保是叶子节点
			if (isLeaf(root)) {
				return true;
			}
		}
		bool has = false;
		if (root->left != nullptr) {
			has = hasPathSum(root->left, targetSum - root->val);
		}
		if (not has && root->right != nullptr) {
			has = hasPathSum(root->right, targetSum - root->val);
		}
		return has;
	}
	// 返回所有成立的路径
	vector<vector<int>> paths;
	vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
		vector<int> path;
		dfs(root, path, targetSum); // 每层函数的参数就是当前步骤的状态码
		return paths;
	}
	void dfs(TreeNode* root, vector<int>& path, int targetSum) {
		if (root == nullptr) {
			return;
		}
		if (root->val == targetSum && root->left == nullptr && root->right == nullptr) {
			path.push_back(root->val);
			paths.push_back(path);
			path.pop_back();
			return;
		}
		path.push_back(root->val);
		dfs(root->left, path, targetSum - root->val);
		dfs(root->right, path, targetSum - root->val);
		path.pop_back();
	}
};
