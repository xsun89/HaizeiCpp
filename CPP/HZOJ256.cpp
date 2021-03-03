//
// Created by Xin Sun on 2021-03-02.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<pair<long, long>> data;
    long n;
    cin >> n;

    for (long i = 0, a, b; i <= n; i++){
        cin >> a >> b;
        data.push_back(make_pair(a, b));
    }

    sort(data.begin() + 1, data.end(),
         [](const pair<long, long> &x, const pair<long, long> &y){
        return x.first * x.second - y.first < y.first * y.second;
    });

    long ans = 0;
    long p = data[0].first;
    for(long i = 1; i <= n; i++){
        ans = max(ans, p / data[i].second);
        p *= data[i].first;
    }

    cout << ans << endl;
}
