//
// Created by Xin Sun on 2021-03-24.
//
#include <iostream>

using namespace std;

class Solution{
public:
    Solution(){
        cout << "default constructor" << endl;
    }
    Solution(int v) : x(v) {
        cout << "set value constructor" << endl;
    }
    Solution(const Solution& s) :x(s.x) {
        cout << "copy constructor" << endl;
    }

    Solution(const Solution&& s) :x(s.x) {
        cout << "moving constructor" << endl;
    }

    Solution &operator=(const Solution& s){
        cout << "= operator" << endl;
        this->x = s.x;
        return *this;
    }
    void print(){
        cout << this->x << endl;
    }
    ~Solution(){
        cout << "destructor" << endl;
    }
private :
    int x;
};
int add(int a, int b){
    //cout << a + b << endl;
    return a + b;
}
int main() {
    //Solution s(10);
    //Solution c(20);
    function<int()> func = bind(add, 1, 2);
    cout << func() << endl;
    //c = s;
    //c.print();

    return 0;
}