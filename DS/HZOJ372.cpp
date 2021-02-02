//
// Created by Xin Sun on 2021-01-29.
//

#include <iostream>
using namespace std;

#define MAX_N 500000
class Queue {
public:
    Queue(int *arr): arr(arr){
        tail = 0;
        head = 0;
    }
    void push(int i)
    {
        while(tail - head && arr[q[tail - 1]] > arr[i]) tail--;
        q[tail++] = i;

        return;
    }
    void pop(){
        head++;
        return;
    }
    int size(){
        return tail - head;
    }
private:
    int *arr;
    int q[MAX_N + 5], head, tail;
};

int a[MAX_N + 5], b[MAX_N + 5];
int n;
Queue q1(a), q2(b);

void read()
{
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    for (int i = 0; i < n; i++){
        cin >> b[i];
    }

    return;
}
int main()
{
    read();
    int p;
    for(p = 0; p < n; p++){
        q1.push(p);
        q2.push(p);
        if(q1.size() != q2.size()){
            break;
        }
    }
    cout << p << endl;
    return 0;
}