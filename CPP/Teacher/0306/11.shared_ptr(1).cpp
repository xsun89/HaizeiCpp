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

namespace haizei {

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

class shared_ptr {
public :
    shared_ptr();
    shared_ptr(A *);
    shared_ptr(const shared_ptr &);
    int use_count();
    A *operator->();
    A &operator*();
    ~shared_ptr();

private:
    int *cnt;
    A *obj;
};

shared_ptr::shared_ptr() : obj(nullptr), cnt(nullptr) {}
shared_ptr::shared_ptr(A *obj) : obj(obj), cnt(new int(1)) {}
shared_ptr::shared_ptr(const shared_ptr &p) : obj(p.obj), cnt(p.cnt) { *p.cnt += 1; }
int shared_ptr::use_count() { return cnt ? *cnt : 0; }
A *shared_ptr::operator->() { return obj; }
A &shared_ptr::operator*() { return *obj; }
shared_ptr::~shared_ptr() {  
    if (cnt != nullptr) {
        *cnt -= 1;
        if (*cnt == 0) delete obj;
        obj = nullptr;
        cnt = nullptr;
    }
}

} // end of haizei

int main() {
    haizei::A *p1 = new haizei::A();
    p1 = nullptr;
    haizei::shared_ptr p2(new haizei::A());
    cout << p2.use_count() << endl; // 1
    haizei::shared_ptr p3 = p2;
    p2->x = 123; p2->y = 456;
    (*p2).x = 456;
    cout << p2.use_count() << endl; // 2
    p2 = nullptr; // 自动析构
    cout << p3.use_count() << endl; // 1
    return 0;
}
