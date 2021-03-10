//
// Created by Xin Sun on 2021-03-04.
//

#include <iostream>
using namespace std;

class A{
public:
    A(){
        cout << "default constructor" << endl;
    }
    A(const A &a){
        cout << "copy constructor" << endl;
    }
    A(int x): x(x){
        cout <<"transform constructor" << endl;
    }

    int x;
};

A func(){
    A temp(10);
    cout << "&temp : " << &temp << endl;
    return temp;
}

int main()
{
    A a = func();
    cout << "&a : " << &a << endl;
    cout << a.x << endl;
    return 0;
}