/*************************************************************************
	> File Name: 1.cat.cpp
	> Author: FlappyEcho 
	> Mail: 
	> Created Time: Sat 06 Mar 2021 07:04:17 PM CST
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

class Animal {
public:
    Animal(string name = "mimi") : _name{name} {
        cout << "animal default constructor" << endl;
    }
    Animal(const Animal& a) {}
    ~Animal() {
        cout << "animal default distructor" << endl;
    }
    void say() {
        cout << "my name is " << _name << endl;
    }
    void rename(string name) {
        this->_name = name;
    }
protected:
    string _name;
};

class Cat : public Animal {
public:
    //显示调用父类构造函数
    Cat() : Animal("Cat mimi"){
        cout << "Cat default constructor" << endl;
    }
    Cat(const Cat& a) : Animal(const Animal& b) {}
    ~Cat() {
        cout << "cat default distructor" << endl;
    }
    void say1() {
        cout << "mmmmmmh, my name is " << _name << endl;
    }
};

class Tiger : public Cat {
public:
    void say2() {
        cout << "gaoooooo, my name is " << _name << endl;
    }
};

class A {
public:
    A() : x(123) {}
    int x;
};

class B : public A {
public:
    void setX(int val) { this->x = val; return; }
};

class C : public A {
public:
    int getX() { return this->x; }
};

class D :public B, public C {};


int main() {
    cout << sizeof(Animal) << " " << sizeof(Cat) << endl;
    Cat c;
    c.say1();
    Animal *p = &c;
    D d;
    cout << "getX : " << d.getX() << endl;
    d.setX(10000);
    cout << "getX : " << d.getX() << endl;
    
    return 0;
}
