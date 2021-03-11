//
// Created by Xin Sun on 2021-03-11.
//

#include <iostream>
#include <algorithm>
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
    vector_queue() {
        make_heap(data.begin(), data.end());
    }
    void push(int x) override {
        data.push_back(x);
        push_heap(data.begin(), data.end()) ;
        return;
    }
    void pop() override {
        pop_heap(data.begin(), data.end());
        data.pop_back();
        return;
    }
    bool empty() override {
        return data.empty();

    }
    int top() override {
        return data.front();
    }
    int size() override {
        return data.size();
    }
private:
    vector<int> data;
};

class heap_queue : public IQueue, public vector<int> {
public :
    void push(int x) override {
        push_back(x);
        up_maintain(size());
        return;
    }
    void pop() override {
        if(empty()) return;
        std::swap(at(0), at(size() - 1));
        pop_back();
        down_maintain(size());
        return;
    }
    bool empty() override {
        empty();
    }
    int top() override {
        if(empty()) return 0;
        return at(0);
    }
    int size() override {
        return size();
    }
private:
    void up_maintain(int);
    void down_maintain(int);
};

void heap_queue::up_maintain(int ind) {
    return;
}

void heap_queue::down_maintain(int ind){
    return;
}

int main() {

    srand(time(0));
    vector_queue q1;
    heap_queue q2;
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        q1.push(val);
        cout << "push q1 : " << val << endl;
    }
    while (!q1.empty()) {
        cout << q1.top() << " ";
        q1.pop();
    }
    cout << endl;


    return 0;
}
