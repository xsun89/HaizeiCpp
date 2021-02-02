//
// Created by Xin Sun on 2021-01-20.
//

#include <iostream>
using namespace std;

#define MAX_N 300000
int queue[MAX_N + 5];
int value[MAX_N + 5];

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++){
        cin >> value[i];
    }

    int head = 0, tail = 0;
    for (int i = 1; i <= n; i++){
        while (tail - head && value[queue[tail - 1]] > value[i]){
            tail--;
        }
        queue[tail++] = i;
        if(queue[head] <= i - k) head++;
        if(i >= k){
            i > k && cout << " ";
            cout << value[queue[head]];
        }
    }
    cout << endl;
    head = 0, tail = 0;
    for (int i = 1; i <= n; i++){
        while (tail - head && value[queue[tail - 1]] < value[i]){
            tail--;
        }
        queue[tail++] = i;
        if(queue[head] <= i - k) head++;
        if(i >= k){
            i > k && cout << " ";
            cout << value[queue[head]];
        }
    }
    return 0;
}