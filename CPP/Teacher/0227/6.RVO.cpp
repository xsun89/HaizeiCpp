/*************************************************************************
	> File Name: 6.RVO.cpp
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

class Data {
public :
    Data() {
        cout << "Data default constructor" << endl;
    }
    Data(const Data &a) {
        cout << "Data copy constructor" << endl;
    }
};

class A {
public :
    A() {
        cout << this << " : default construcotr" << endl;
    }
    A(int x) : x(x) {
        cout << this << " : transform constructor" << endl;
    }
    /*A(const A &a) : x(a.x) {
        cout << this << " : copy constructor" << endl;
    }*/
    A &operator=(const A &a) {
        cout << this << " : operator=" << endl;
        return *this;
    }
    int x;
    Data d;
};

A func() {
    A temp(69);
    cout << "&temp = " << &temp << endl;
    return temp;
}

int main() {
    A a = func();
    cout << "&a = " << &a << endl;
    cout << a.x << endl;
    cout << endl << endl << "=============" << endl;
    a = func();
    return 0;
}
