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
    void reg1() {
        cout << "reg1" << endl;
    }
    void reg2() {
        cout << "reg2" << endl;
    }
    void reg3() {
        cout << "reg3" << endl;
    }
    int x, y;
};


typedef void (*func)(void *);
int main()
{
    A a;
    A b;
    //every member function has hidden this pointer
    ((void **)(&a))[0] = ((void **)(&b))[0] ;
    ((func **)(&a))[0][0](&a); //cast (&a) to (func **)  vtable first function is (func **)
    //class member function pointer
    void (A::*p1)();
    p1 = &A::reg1;
    (a.*p1)();

    //array of class member function pointer
    void (A::*p[3])();
    p[0] = &A::reg1;
    p[1] = &A::reg2;
    p[2] = &A::reg3;

    for (int i = 0; i < 10; i++)
    {
        (a.*p[rand()%3])();
    }

    int A::*q;
    q = &A::x;
    cout << (a.*q) << endl;
    return 0;
}