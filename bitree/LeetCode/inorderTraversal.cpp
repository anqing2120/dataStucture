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

vector<int> inorderTraversal(TreeNode* root){
	vector<int> ans;
	do{
		if(nullptr == root){
			break;
		}

		stack<TreeNode*> stk;
		TreeNode* ptr=root; // ptr points to the root

		do{
			label:
			if(stk.empty() || nullptr == ptr){
				break;
			}
			while(ptr){
				stk.push(ptr);
				ptr = ptr->left;
			} // 来到最左下的空节点 ptr == null
			// print(left:null)
			label2:
			TreeNode* father = stk.top(); stk.pop();
			ans.push_back(father->val); // print(root)
			ptr = father->right;

			if(ptr){
				goto label; // 右边儿子不空，继续往它的左下走
			}else{
				goto label2; // 右边儿子也是空，继续弹出父节点
			}
		}while(true);
	}while(false);

	return ans;
}

// 简化后栈的写法 注意到栈里面上下节点的关系是 下面是父亲节点 上面是左孩子
vector<int> inorderTraversal1(TreeNode* root){
	vector<int> res;

	do{
		if(nullptr == root){
			break;
		}
		stack<const TreeNode* > stk; // node cannot be changed
		const TreeNode* ptr = root; // pointer to now node

		while(!stk.empty() || nullptr != ptr){
			if(nullptr != ptr){ // pointer not null
				stk.push(ptr); // record the path
				ptr = ptr->left;// just go left
			}else{ // ptr is null
				// res.push_back(-1) means left node is null
				const TreeNode* father = stk.top(); // get father node
				stk.pop();
				res.push_back(father->val); // print father node
				ptr = father->right;// now change to right
			}
		}

	}while(false);

	return res;
}

// morris
vector<int> inorderTraversal2(TreeNode* root){


	return vector<int>();

}
int main()
{
	vector<int> pre_tree{7,6,-1,2,-1,-1,3,4,-1,-1,5,-1,-1};
	TreeNode* root = creatTree(pre_tree);
	inOrder(root);
	NEXTLINE;

	vector<int> level = inorderTraversal2(root);
	printVector(level);
}