//
// Created by Xin Sun on 2021-03-02.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> data;
    int n;
    cin >> n;
    for (int i = 0, a; i < n; i++)
    {
        cin >> a;
        data.push_back(a);
    }

    //sort(data.begin(), data.end());
    nth_element(data.begin(), data.begin() + n/2, data.end());
    int mid = data[n/2];
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += abs(data[i] - mid);
    }

    cout << sum << endl;
    return 0;
}