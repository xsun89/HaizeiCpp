//
// Created by Xin Sun on 2021-03-02.
//

#include <iostream>
#include <queue>

using namespace std;

template <typename T>
class cmp{
public:
    bool operator()(const T& a, const T& b)
    {
        return a > b;
    }
};

int main()
{
    priority_queue<int, vector<int>, cmp<int>> queue;
    int n;
    cin >> n;
    for(int i = 0, a; i < n; i++){
        cin >> a;
        queue.push(a);
    }
    int sum = 0;
    for(int i = 1; i < n; i++){
        int a = queue.top();
        queue.pop();
        int b = queue.top();
        queue.pop();
        sum += a + b;
        queue.push(a + b);
    }
    cout << sum << endl;
    return 0;
}