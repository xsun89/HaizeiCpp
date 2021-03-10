/*************************************************************************
	> File Name: 5.priority_queue.cpp
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

class IQueue {
public :
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual bool empty() = 0;
    virtual int top() = 0;
    virtual int size() = 0;
};

class vector_queue : public IQueue {
public :
    void push(int x) override {}
    void pop() override {}
    bool empty() override {}
    int top() override {}
    int size() override {}
};

class heap_queue : public IQueue {
public :
    void push(int x) override {}
    void pop() override {}
    bool empty() override {}
    int top() override {}
    int size() override {}
};

int main() {
    
    
    
    
    return 0;
}
