//
// Created by Xin Sun on 2021-02-26.
//
#include <iostream>

using namespace std;

int inv[7 + 5];

int main()
{
    inv[1] = 1;
    for (int i = 2; i < 7; i++){
        inv[i] = (((-(7 / i) * inv[7 % i]) % 7) + 7) % 7;
        cout << i << " : " << inv[i] << endl;
    }
    return 0;
}
