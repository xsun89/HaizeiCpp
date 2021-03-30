/*************************************************************************
	> File Name: 9.function.cpp
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
using namespace std;

namespace haizei {

template<typename T, typename ...ARGS> 
class base {
public :
    virtual T run(ARGS...) = 0;
    virtual ~base() {}
};

template<typename T, typename ...ARGS> 
class normal_func : public base<T, ARGS...> {
public :
    typedef T (*FUNC_T)(ARGS...); 
    normal_func(FUNC_T func) : func(func) {}
    T run(ARGS ...args) override {
        return func(forward<ARGS>(args)...);
    }

private:
    FUNC_T func;
};

template<typename C, typename T, typename ...ARGS> 
class functor : public base<T, ARGS...> {
public :
    functor(C obj) : obj(obj) {}
    T run(ARGS ...args) override {
        return obj(forward<ARGS>(args)...);
    }

private:
    C obj;
};

template<typename T, typename ...ARGS> class function;
template<typename T, typename ...ARGS>
class function<T(ARGS...)> {
public :
    function(T (*ptr)(ARGS...)) : fptr(new normal_func<T, ARGS...>(ptr)) {}
    template<typename C>
    function(C &&object) : fptr(new functor<C, T, ARGS...>(object)) {}
    function(const function<T(ARGS...)> &obj) {
        function *fun = new functor<T(ARGS...)>(obj);

    } // 拷贝构造
    function(function<T(ARGS...)> &&obj) {
        fptr = obj.fptr;
    }      // 移动构造
    
    function &operator=(const function &obj) {}
    function &operator=(function &&obj) {}
    function &operator=(const function &obj) const {}
    function &operator=(function &&obj) const {}

    T operator()(ARGS ...args) {
        return fptr->run(forward<ARGS>(args)...);
    }
    
    ~function() {
        if (fptr != nullptr) delete fptr;
        fptr = nullptr;
    }

private:
    base<T, ARGS...> *fptr;
};

} // end of haizei

void func(int a, int b) {
    cout << "normal function" << endl;
    return ;
}

class ADD_FUNC {
public :
    ADD_FUNC() : x(0) {}
    void operator()(int a, int b) {
        x += a + b;
        cout << "class object : " << x << endl;
        return ;
    }
    int x;
};

int main() {
    ADD_FUNC add;
    function<void(int, int)> F1 = func;
    function<void(int, int)> F2 = add;
    F1(3, 4);
    F2(3, 4);
    F2(5, 6);
    haizei::function<void(int, int)> f1 = func;
    haizei::function<void(int, int)> f2 = add;
    f1(3, 4);
    f2(3, 4);
    f2(5, 6);
    return 0;
}
