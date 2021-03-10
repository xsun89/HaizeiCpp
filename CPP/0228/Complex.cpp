//
// Created by Xin Sun on 2021-03-05.
//
#include <iostream>

using namespace std;

class Complex {
public:
    Complex(): x(0), y(0){}
    Complex(int x, int y): x(x), y(y){}
    Complex(const Complex& a) = default;
    ~Complex(){}
    Complex operator+(const Complex& a);
    Complex operator-(const Complex& a);
    Complex operator*(const Complex& a);
    Complex operator/(const Complex& a);
private:
    friend ostream &operator<<(ostream &out, Complex &a);
    int x, y;
};
Complex Complex::operator+(const Complex& a){
    Complex tmp;
    tmp.x = this->x + a.x;
    tmp.y = this->y + a.y;
    return tmp;
}

Complex Complex::operator-(const Complex& a){
    Complex tmp;
    tmp.x = this->x - a.x;
    tmp.y = this->y - a.y;
    return tmp;
}

Complex Complex::operator*(const Complex& a){
    Complex temp;
    temp.x = this->x * a.x - this->y * a.x;
    temp.y = this->y * a.x + this->x * a.y;
    return temp;
}

Complex Complex::operator/(const Complex& a){
    Complex tmp;
    int k = (a.x * a.x + a.y * a.y);
    tmp.x = (this->x * a.x + this->y * a.y) / k;
    tmp.y = (this->y * a.x - this->x * a.y) / k;
    return tmp;
}
ostream &operator<<(ostream &out, Complex &a){
    if (a.x != 0) out << a.x;
    if (a.y > 0 && a.x != 0) out << "+";
    if (a.y > 0) out << a.y << "i";
    else if (a.y < 0)out <<  a.y << "i";
    if (a.x == 0 && a.y == 0) out << 0;
    return out;
}
int main()
{
    Complex a;
    Complex b(1, 2);
    Complex c = a + b;
    cout << c << endl;

    Complex d(-1, -20);
    cout << d << endl;
    return 0;
}
