//
// Created by Xin Sun on 2021-03-17.
//
#include <iostream>
using namespace std;

template<int t, int n>
struct isPrime {
    static constexpr int r = ((t % n == 0) + isPrime<t, n - 1>::r);
};

template<int t>
struct isPrime<t, 1> {
    static constexpr int r = 0;
};

template<int n>
struct is_prime{
    static constexpr char *r = (char *)(isPrime<n, n - 1>::r ? "No" : "Yes");
};

int main(){
    cout << is_prime<5>::r << endl;
    return 0;
}