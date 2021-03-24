/*************************************************************************
	> File Name: 8.bind.cpp
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

void func(int x) {
    cout << x << endl;
    return ;
}

void add(int a, int b) {
    cout << a << " + " << b << endl;
    return ;
}

void test_ref(int &x) {
    x += 1;
    cout << "test_ref function" << endl;
    return ;
}

int main() {
    func(123);
    function<void()> f = bind(func, 123);
    cout << "==========" << endl;
    f();
    function<void(int)> add3 = bind(add, 3, std::placeholders::_1);
    add3(45);
    add3(89);
    add3(100);
    function<void(int, int)> add2 = bind(add, std::placeholders::_2, std::placeholders::_1);
    add2(3, 4);
    int n = 0;
    function<void()> ref_func = bind(test_ref, ref(n));
    cout << n << endl;
    ref_func();
    cout << n << endl;

    auto weird_func = bind(add, placeholders::_4, placeholders::_1);
    weird_func(1, 2, 3, 4);
    return 0;
}
