/*************************************************************************
	> File Name: 11.shared_ptr.cpp
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
#include <memory>
using namespace std;

class A {
public :
    A() { 
        cout << "default constructor" << endl;
    }
    int x, y;
    ~A() {
        cout << "destructor" << endl;
    }
};

int main() {
    A *p1 = new A();
    p1 = nullptr;
    shared_ptr<A> p2(new A());
    cout << p2.use_count() << endl; // 1
    shared_ptr<A> p3 = p2;
    p2->x = 123; p2->y = 456;
    (*p2).x = 456;
    cout << p2.use_count() << endl; // 2
    p2 = nullptr; // 自动析构
    cout << p3.use_count() << endl; // 1
    return 0;
}
