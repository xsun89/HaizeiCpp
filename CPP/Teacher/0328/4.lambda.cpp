/*************************************************************************
	> File Name: 4.lambda.cpp
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

function<int(int)> func(int x) {
    int n = 123;
    return [&](int k) -> int { return k * n + x; };
}

int main() {
    auto test = func(3);
    cout << test(3) << endl;
    auto add = [](int a, int b) -> int { return a + b; };
    auto add3 = [](int a, int b) -> int { return a + b; };
    function<int(int, int)> add2 = add;
    cout << add(3, 4) << endl;
    cout << typeid(add).name() << endl;
    cout << typeid(add2).name() << endl;
    cout << typeid(add3).name() << endl;
    int n = 12;
    auto times = [&](int k) {
        return n * k;
    };
    cout << times(3) << endl; // 36, n = 12
    n = 14;
    cout << times(3) << endl; // 36, n = 12
    cout << test(3) << endl;
    return 0;
}
