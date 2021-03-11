//
// Created by Xin Sun on 2021-03-11.
//
#include <iostream>
using namespace std;

class A{
public:
    virtual void say(){
        cout << "A" << endl;
    }
    virtual ~A(){}
};

class B : public A{
public:
    void say(){
        cout << "B" << endl;
    }
    virtual ~B(){}
};

class C : public A{
public:
    void say(){
        cout << "C" << endl;
    }
    virtual ~C(){}
};

int main()
{
    srand(time(NULL));
    A* p;
    switch(rand() % 2){
        case 0: p = new B(); break;
        case 1: p = new C(); break;
    }
    //dynamic_cast cast derived object to it's bass object
    //if type matches, return it, if not match return NULL. rely on virtual
    //table to determine.
    cout << dynamic_cast<B *>(p) << endl;
    cout << dynamic_cast<C *>(p) << endl;

    return 0;
}