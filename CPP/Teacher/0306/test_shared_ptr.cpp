/*************************************************************************
	> File Name: test_shared_ptr.cpp
	> Author: FlappyEcho 
	> Mail: 
	> Created Time: Sat 06 Mar 2021 03:13:41 PM CST
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;

class A {
public:
    A() {
        cout << "default constructor" << endl;
    }
    ~A() {
        cout << "destructor" << endl;
    }
    int x, y;
};

class testptr {
public:
    testptr() = default;
    testptr(A a) : a{&a} {}
    testptr(A* a) : a{a} {}
    ~testptr() = default;
private:
    A* a;

    static int cout_use;
};

int main() {
    


    return 0;
}
