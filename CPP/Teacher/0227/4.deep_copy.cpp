/*************************************************************************
	> File Name: 4.deep_copy.cpp
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

class Array {
public :
    Array(int n = 10) {
        this->n = n;
        data = new int[n];
    }
    Array(const Array &a) {
        this->n = a.n;
        this->data = new int[this->n];
        for (int i = 0; i < this->n; i++) {
            this->data[i] = a.data[i];
        }
    }
    size_t size() const { return this->n; }
    int &operator[](int ind) {
        if (ind < 0 || ind >= n) return end;
        return data[ind];
    }
    const int &operator[](int ind) const {
        if (ind < 0 || ind >= n) return this->end;
        return this->data[ind];
    }

private:
    int *data, end;
    size_t n;
};

ostream &operator<<(ostream &out, const Array &a) {
    out << "Array(" << &a << ") : ";
    for (int i = 0; i < a.size(); i++) {
        i && out << " ";
        out << a[i];
    }
    return out;
}

int main() {
    Array a;
    for (int i = 0; i < a.size(); i++) {
        a[i] = rand() % 100;
    }
    cout << a << endl;
    Array b = a;
    cout << b << endl;
    b[1] = 18432;
    cout << a << endl;
    cout << b << endl;
    return 0;
}
