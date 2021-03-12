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

class vector_queue_2 : public IQueue, public vector<int> {
public :
    void push(int x) override {
        push_back(x);
        return;
    }
    void pop() override {
        if(empty()) return;
        iterator p = begin();
        for(auto it = begin(); it != end(); ++it){
            if(*it > *p) p = it;
        }
        erase(p);
        return;
    }
    bool empty() override {
        return size() == 0;;

    }
    int top() override {
        if(empty()) return 0;
        int ans = 0;
        for (int i = 1; i < size(); ++i){
            ans = max(ans, at(i));
        }
        return ans;
    }
    int size() override {
        return vector<int>::size();
    }
private:
};


class heap_queue : public IQueue, public vector<int> {
public :
    heap_queue(){
        cout << "heap_queue" <<endl;
        push_back(0);
    }
    void push(int x) override {
        push_back(x);
        up_maintain(size());
        return;
    }
    void pop() override {
        if(empty()) return;
        std::swap(at(1), at(size()));
        pop_back();
        down_maintain(size());
        return;
    }
    bool empty() override {
        return size() == 1;
    }
    int top() override {
        if(empty()) return 0;
        return at(1);
    }
    int size() override {
        return size() + 1;
    }
private:
    void up_maintain(int);
    void down_maintain(int);
};

void heap_queue::up_maintain(int ind) {
    while(ind / 2 > 0 && at(ind / 2) > at(ind))
    {
        std::swap(at(ind/2), at(ind));
        ind = ind / 2;
    }
    return;
}

void heap_queue::down_maintain(int ind){
    while(ind * 2 <= size()){
        int tmp = ind;
        if(at(ind * 2) < at(ind)) tmp = 2 * ind;
        if(ind * 2 + 1 <= size() && at(ind * 2 + 1) < at(ind)) tmp = 2 * ind + 1;
        if(tmp == ind) break;
        std::swap(at(ind), at(tmp));
        ind = tmp;
    }
    return;
}

int main() {

    srand(time(0));
    vector_queue_2 q1;
    heap_queue q2;
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        q1.push(val);
        cout << "push q1 : " << val << endl;
        cout << q1.size() << endl;
    }
    while (!q1.empty()) {
        cout << q1.top() << " ";
        q1.pop();
    }
    cout << endl;
    cout << "--------------------" << endl;
/*
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        q2.push(val);
        cout << "push q2 : " << val << endl;
    }
    while (!q2.empty()) {
        cout << q2.top() << " ";
        q2.pop();
    }
    cout << endl;
*/
    return 0;
}
