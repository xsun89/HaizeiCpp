//
// Created by Xin Sun on 2021-03-17.
//
#include <iostream>
using namespace std;

template<int n>
struct sum{
    static constexpr int r = n + sum<n - 1>::r;
};

template<>
struct sum<1>{
    static constexpr int r = 1;
};

template<int n>
struct isEven {
    static constexpr int r = !(n % 2);
};
template<int n>
struct judge{

};

template<>
struct judge<0>{
    static constexpr char *r = "not even";
};

template<>
struct judge<1>{
    static constexpr char *r = "even";
};
template<int n>
struct is_even {
    static constexpr char *r = judge<isEven<n>::r>::r;
};


int main(){
    cout << sum<5>::r << endl;
    cout << is_even<4>::r << endl;
    return 0;
}
