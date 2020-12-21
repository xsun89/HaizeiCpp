#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> arr;
    int n;
    cin >> n;
    int data;
    for (int i = 0; i<n; i++){
        cin >> data;
        arr.push_back(data);
    }

    sort(arr.begin(), arr.end());
    int k = n/2;
    int sum = 0;
    for(int i = 0; i<n; i++){
        sum += abs(arr[k] - arr[i]);
    }

    cout << sum << endl;
}
