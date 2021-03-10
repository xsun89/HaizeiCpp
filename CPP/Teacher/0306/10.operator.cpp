/*************************************************************************
	> File Name: 10.operator.cpp
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

class Point {
public :
    Point();
    Point(int x, int y);
    Point operator+(const Point &);
    Point &operator+=(int);

    
private:
    friend Point operator+(const Point &, const Point &);
    friend ostream &operator<<(ostream &, const Point &);
    int x, y;
};

Point::Point() : Point(0, 0) {}
Point::Point(int x, int y) : x(x), y(y) {}

Point &Point::operator+=(int n) {
    x += n, y += n;
    return *this;
}

Point Point::operator+(const Point &a) {
    cout << "inner operator+" << endl;
    Point c(x + a.x, y + a.y);
    return c;
}

Point operator+(const Point &a, const Point &b) {
    cout << "outer operator+" << endl;
    Point c(a.x + b.x, a.y + b.y);
    return c;
}

ostream &operator<<(ostream &out, const Point &a) {
    out << "(" << a.x << ", " << a.y << ")";
    return out;
}

int main() {
    Point a(3, 4);
    Point b(7, 9);
    Point c = a + b;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    (a += 2) += 2;
    cout << a << endl;
    return 0;
}
