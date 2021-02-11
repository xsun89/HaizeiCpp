/*************************************************************************
	> File Name: 2.jian56.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0, a1, b1;
        for (int i = 0, c; i < nums.size(); i++) {
            c = nums[i];
            a1 = (a & ~b & ~c) | (~a & b & c);
            b1 = (~a & b & ~c) | (~a & ~b & c);
            a = a1;
            b = b1;
        }
        return b;
    }
};

int main() {
    

    return 0;
}
