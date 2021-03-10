//
// Created by Xin Sun on 2021-03-09.
//
#include <iostream>

using namespace std;

class A
{
public:
    A(){
        cout << "default constructor" << endl;
        cout << "";
    }
    ~A(){
        cout << "default destructor" << endl;
    }
    int getX(){
        return x;
    }

    int x;
};

class sharedPtr
{
public:
    sharedPtr() : obj(nullptr), cnt(nullptr){}
    sharedPtr(A *a) : obj(a), cnt(new int(1)){
        cout << "sharedPtr(A *a) " << *cnt << endl;
    }
    sharedPtr(const sharedPtr &p) : obj(p.obj), cnt(p.cnt){
        cout << "sharedPtr(const sharedPtr &p) " << endl;
        *cnt += 1;
    }

    sharedPtr &operator=(const sharedPtr &p){
        cout << "sharedPtr &operator= " << cnt << "    " << *cnt << endl;
        if(this->obj != p.obj){

            if(cnt != nullptr) {
                cout << "*cnt" << *cnt << endl;
                *cnt -= 1;
                cout << usedCount() << endl;
                if(*cnt == 0){
                    delete obj;
                    delete cnt;
                    this->obj = nullptr;
                    this->cnt = nullptr;
                }
            }
        }
        return *this;
    }
    ~sharedPtr(){
        cout << "~sharedPtr " << cnt <<  "--" << *cnt << endl;
        if(cnt != nullptr) {
            *cnt -= 1;
            if(*cnt == 0){
                delete obj;
                delete cnt;
                cnt = nullptr;
                obj = nullptr;
            }
        }
    }
    A *operator->(){
        return obj;
    }
    A &operator*(){
        return *obj;
    }
    int usedCount(){
        return cnt != nullptr ? *cnt : 0;
    }
private:
    A *obj;
    int *cnt;
};

int main()
{
    A *p1 = new A();
    p1 = nullptr;
    sharedPtr p2(new A());
    cout << p2.usedCount() << endl; // 1
    sharedPtr p3 = p2;
    p2->x = 123;
    (*p2).x = 456;
    cout << p3->getX() << endl;
    cout << p2.usedCount() << endl; // 2
    p2 = nullptr; // 自动析构
    cout << p3.usedCount() << endl; // 1
}