/*************************************************************************
	> File Name: 1.inv.cpp
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
int inv[7] = {0};

int main() {
    inv[1] = 1;
    for (int i = 2; i < 7; i++) {
        inv[i] = ((-(7 / i) * inv[7 % i]) % 7 + 7) % 7;
        cout << i << " : " << inv[i] << endl;
    }
    return 0;
}
