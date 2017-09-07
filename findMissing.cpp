//  这道题的挑战是 额外空间O(1),时间复杂度O(n)
//  深思熟虑后我决定放弃
//  从入门到放弃哈哈哈哈




class Solution {
public:
	/**
	* @param nums: a vector of integers
	* @return: an integer
	*/
	int findMissing( vector <int> nums) {               //没想到vector会用到这么多，还是太菜啊
		// write your code here
		int size = nums.size();
		int *num = new int[size + 1];
		while (!nums.empty()) {
			num[nums.back()] = nums.back();
			nums.pop_back();

		}
		for (int i = 1; i<size; i++) {
			if (num[i] != i)
				return i;
		}
		return size;
	}
};