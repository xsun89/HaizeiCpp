//
// Created by Xin Sun on 2021-03-14.
// gcc -c cpp file
// nm -C object file;
#include <iostream>
using namespace std;
class A{
public:
    A() = delete;
    A(int x) : x(x){}
    A operator+(const A&a);
    friend ostream &operator<<(ostream & out, const A&);
private:
    int x;
};
A A::operator+(const A& a)
{
    return A(a.x + this->x);
}

ostream& operator<<(ostream &out, const A& a){
    out << a.x << endl;

    return out;
}
template<typename T, typename K>
auto add(T a1, K a2) -> decltype(a1 + a2)
{
    return a1 + a2;
}

int main()
{
    A a1(10);
    A b1(20);
    cout << a1 + b1 << endl;
    cout << add(a1, b1) << endl;
    int x = 2;
    double y = 1.2;
    cout << add(x, y) << endl;
    return 0;
}
