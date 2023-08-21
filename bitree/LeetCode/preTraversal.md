Morris 先序遍历是一种使用线索化二叉树（Threaded Binary Tree）的算法，用于在不使用栈的情况下对二叉树进行先序遍历。

常规的先序遍历是以递归方式或使用栈实现的，而 Morris 先序遍历是一种空间复杂度为O(1)的方法。它通过修改二叉树的指针，将空闲的右子节点指向遍历节点的直接后继节点，从而实现先序遍历。

Morris 先序遍历的步骤如下：

初始化当前节点为根节点 current = root:
1. 当 current 不为空时，执行以下循环：
   - 如果 current 的左子节点为空，输出 current 的值，然后将 current 指向其右子节点
   - 如果 current 的左子节点不为空：
     - 找到 current 左子树上的最右子节点，称为 predecessor
     - 如果 predecessor 的右子节点为空，将其右子节点指向 current。输出 current 的值，然后将 current 指向其左子节点
     - 如果 predecessor 的右子节点不为空，表示当前子树以遍历完毕，将其右子节点置空。然后将 current 指向其右子节点
   
2. 重复步骤2，直到 current 为空

通过这种方式，每个节点会被访问两次，时间复杂度为 O(n)，其中 n 为节点数。空间复杂度为 O(1)。
利用 Morris 先序遍历，可以在**不使用额外空间**的情况下对二叉树进行先序遍历。