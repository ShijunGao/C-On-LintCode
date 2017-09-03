class Solution {

public:
    /**
     * @param num a positive number
     * @return true if it's a palindrome or false
     */
    bool palindromeNumber(int num) {
		// Write your code here
		if (num < 0) {
			return false;
		}
		if (num >= 10) {
			int a[32];							//开始用的stack，想想一个数组也就解决了
			int temp = num;
			int i = 0;
			for (i; temp != 0; i++) {
				a[i] = temp % 10;
				temp = temp / 10;
			}
			i--;
			for (int m = 0; m != i&&(i+1!=m); m++) {			//注意i为奇数的情况
				if (a[m] != a[i])
					return false;
				i--;
			}
		}
		return true;
	}
};