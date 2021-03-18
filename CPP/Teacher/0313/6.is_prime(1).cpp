/*************************************************************************
	> File Name: 6.is_prime.cpp
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

template<int N>
struct is_prime {
    static constexpr int r = 0;
};

template<int n>
struct sum {
    static constexpr int r = n + sum<n - 1>::r;
};

template<>
struct sum<1> {
    static constexpr int r = 1;
};

template<int n>
struct getBad {
    static constexpr int r = (n <= 5);
};

template<int n>
struct getGood {
    static constexpr int r = (n > 5);
};

template<int n, int m> struct judge;
template<>
struct judge<1, 0> {
    static constexpr char *r = (char *)"bad";
};

template<>
struct judge<0, 1> {
    static constexpr char * r = (char *)"good";
};

template<int n>
struct score {
    static constexpr char *r = judge<getBad<n>::r, getGood<n>::r>::r;
};

template<int n>
struct isEven {
    static constexpr int r = !(n % 2);
};

template<int n> struct judge1;
template<>
struct judge1<0> {
    static constexpr char *r = (char *)"no";
};

template<>
struct judge1<1> {
    static constexpr char * r = (char *)"yes";
};
template<int n>
struct is_even {
    static constexpr char *r = judge1<isEven<n>::r>::r;
};

int main() {
    cout << sum<5>::r << endl; // for
    cout << score<10>::r << endl; // good, if
    cout << score<4>::r << endl; // bad, if
    cout << is_even<3>::r << endl; // no
    cout << is_even<4>::r << endl; // yes
    cout << is_prime<2>::r << endl; // 1
    cout << is_prime<13>::r << endl; // 1
    cout << is_prime<25>::r << endl; // 0
    cout << is_prime<27>::r << endl; // 0
    cout << is_prime<9973>::r << endl; // 1
    return 0;
}
