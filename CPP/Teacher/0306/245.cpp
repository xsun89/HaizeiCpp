/*************************************************************************
	> File Name: 245.cpp
	> Author: LXF
	> Mail: 
	> Created Time: Sat Mar  6 14:57:07 2021
 ************************************************************************/

#include<iostream>
using namespace std;

template<typename T>
class shared_ptr{
private:
    T *p;
    int cnt;
public:
    shared_ptr(T *t): p(t), cnt(1){
    }
    shared_ptr(const shared_ptr<T> &t){
        p = NULL;
        (*this) = t;
    }
    ~shared_ptr(){
        free(p);
    }
    int use_count() const{
        return cnt;
    }
    friend shared_ptr operator=(const shared_ptr &);
};

shared_ptr operator=(shared_ptr &a, shared_ptr &b){
    if(a.cnt == 1 && a.p != b.p){
        delete a.p;
    }

    a.cnt = b.cnt + 1;
    b.cnt = a.cnt;

    a.p = b.p;
    return a;
}

int main(){

    return 0;
}
