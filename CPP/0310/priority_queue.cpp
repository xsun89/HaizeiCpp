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
        for (int i = 0; i < size(); ++i){
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
    void push(int x) override {
        push_back(x);
        up_maintain(size());
        return;
    }
    void pop() override {
        if(empty()) return;
        std::swap(at(0), at(size() - 1));
        pop_back();
        down_maintain(1);
        return;
    }
    bool empty() override {
        return size() == 0;
    }
    int top() override {
        if(empty()) return 0;
        return at(0);
    }
    int size() override {
        return this->vector<int>::size();
    }
private:
    void up_maintain(int);
    void down_maintain(int);
};

void heap_queue::up_maintain(int ind) {
    //ind = vector index + 1
    //                  0
    //              1          2
    //          3       4   5      6
    //
    //
    while(ind > 1 && at(ind - 1) > at((ind / 2) - 1))
    {
        std::swap(at(ind - 1), at((ind / 2) - 1));
        ind /= 2;
    }

    return;
}

void heap_queue::down_maintain(int ind){
    while(ind * 2 <= size()){
        int tmp = ind;
        if(at(ind * 2 - 1) < at(tmp - 1)) tmp = 2 * ind;
        if(ind * 2 + 1<= size() && at(ind * 2 ) < at(tmp - 1)) tmp = 2 * ind + 1;
        if(tmp == ind) break;
        std::swap(at(ind - 1), at(tmp - 1));
        ind = tmp;
    }
    return;

}

class heap_queue_2 : public IQueue, public vector<int> {
public :
    void push(int x) override {
        push_back(x);
        up_maintain(size());
        return ;
    }
    void pop() override {
        std::swap(at(0), at(size() - 1));
        pop_back();
        down_maintain(1);
        return ;
    }
    bool empty() override {
        return size() == 0;
    }
    int top() override {
        if (empty()) return 0;
        return at(0);
    }
    int size() override {
        return this->vector<int>::size();
    }

private:
    void up_maintain(int ind) {
        while (ind > 1 && at(ind - 1) > at((ind / 2) - 1)) {
            std::swap(at(ind - 1), at((ind / 2) - 1));
            ind /= 2;
        }
        return ;
    }
    void down_maintain(int ind) {
        while (ind * 2 <= size()) {
            int temp = ind;
            if (at(ind * 2 - 1) > at(temp - 1)) temp = ind * 2;
            if (ind * 2 + 1 <= size() && at(ind * 2) > at(temp - 1)) temp = ind * 2 + 1;
            if (temp == ind) break;
            std::swap(at(temp - 1), at(ind - 1));
            ind = temp;
        }
        return ;
    }
};
int main() {

    srand(time(0));
    vector_queue_2 q1;
    heap_queue_2 q2;
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

    return 0;
}
