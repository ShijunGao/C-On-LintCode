/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */


 class Solution {
public:
	/*
	* @param T1: The roots of binary tree T1.
	* @param T2: The roots of binary tree T2.
	* @return: True if T2 is a subtree of T1, or false.
	*/
	bool isSubtree(TreeNode * T1, TreeNode * T2) {
		// write your code here
		if (T2 == nullptr)
			return true;
		if (T1 == nullptr&&T2 != nullptr)                   //不加判断会导致指针报错，应该是T1遍历完左子树向右跳时出错
			return false;
		if (IsSame(T1, T2))                                 //判断两个二叉树是否相同
			return true;
		if (isSubtree(T1->left, T2))
			return true;
		if (isSubtree(T1->right, T2))
			return true;
		return false;
	}
	bool IsSame(TreeNode * T1, TreeNode * T2) {                         //递归遍历 判断
		if (T1 == nullptr&&T2 == nullptr)
			return true;
		if (T1 == nullptr&&T2 != nullptr)
			return false;
		if (T1 != nullptr&&T2 == nullptr)
			return false;
		if (T1->val != T2->val)
			return false;
		return IsSame(T1->left, T2->left) && IsSame(T1->right, T2->right);
	}
 };