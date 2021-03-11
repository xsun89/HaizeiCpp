//
// Created by Xin Sun on 2021-03-10.
//

#include <iostream>

using namespace std;

class A {
public:
    A() : x(123) {}
    virtual void say() {
        cout << x << endl;
    }
    int x;
};


typedef void (*func)(void *);
int main()
{
    A a;
    A b;
    ((void **)(&a))[0] = ((void **)(&b))[0] ;
    ((func **)(&a))[0][0](&a); //cast (&a) to (func **)  vtable first function is (func **)
    return 0;
}