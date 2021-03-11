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

void judge(A *p){
    //dynamic_cast cast derived object to it's bass object
    //if type matches, return it, if not match return NULL. rely on virtual
    //table to determine.
    if(dynamic_cast<B *>(p)){
        cout << "this is B" << endl;
    }else if(dynamic_cast<C *>(p)){
        cout << "this is C" << endl;
    }else{
        cout << "NULL" << endl;
    }
    return;
}

int main()
{
    srand(time(NULL));
    A* p;
    B* b;
    C* c;
    switch(rand() % 2){
        case 0: p = new B(); break;
        case 1: p = new C(); break;
    }
    judge(p);

    ((void **)&b)[0] = ((void **)&c)[0];
    return 0;
}