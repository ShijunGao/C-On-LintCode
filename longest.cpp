class Solution {
public:
    /*
     * @param s: input string
     * @return: the longest palindromic substring
     */
    string longestPalindrome(string &s) {
		// Write your code here	
		int length=s.length();						//记录得到的子串
		int longest=0;
		int left=0;
		int right=0;
		for(int i=0;i< length ;i++){							//双循环遍历得到所有子串，找到最长回文子串
			for(int j=i+1;j<length;j++){
				int temp=getlength(s.substr(i,j-i+1));
				if(temp>longest){
					longest=temp;
					left=i;
					right=j;
				}
			}
		}
		return s.substr(left,right-left+1);
	}
	int getlength(string s){									//改自Palindrome.cpp
		int length=s.length()-1;
		for(int m=0;m!=length&&(length+1!=m);m++){
			if(s[m]!=s[length])
				return 0;
			length--;		
		}
	return s.length();
	}
};
