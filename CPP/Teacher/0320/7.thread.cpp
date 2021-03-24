/*************************************************************************
	> File Name: 7.thread.cpp
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
#include <thread>
using namespace std;

void func(int x) {
    for (int i = 0; i < x; i++) cout << i << endl;
    return ;
}

void add_one(int &x) {
    cout << "add_one fucntion" << endl;
    x += 1;
    return ;
}

class Task {
public :
    template<typename FUNCTION, typename ...ARGS>
    Task(FUNCTION &&f, ARGS ...args) {
        cout << "Task constructor" << endl;
        this->f = bind(f, forward<ARGS>(args)...);
    }
    void run() {
        f();
    }

private:
    function<void()> f;
};

int main() {
    int n = 8;
    thread t1(add_one, ref(n));
    t1.join();
    Task t2(add_one, ref(n));
    cout << "hello world" << endl;
    t2.run();
    t2.run();
    t2.run();
    cout << n << endl;
    return 0;
}
