/*************************************************************************
	> File Name: 10.random.cpp
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


namespace haizei {
    static int __seed = 3;
    void srand(int seed) {
        __seed = seed;
        return ;
    }
    int rand() {
        return (__seed = __seed * 3 % 101);
    }
} // end of haizei

int main() {
    int n;
    while (cin >> n) {
        haizei::srand(n);
        for (int i = 0; i < 10; i++) {
            cout << haizei::rand() << endl;
        }
    }
    return 0;
}
