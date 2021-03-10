/*************************************************************************
	> File Name: 12.sort.cpp
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

ostream &operator<<(ostream &out, const vector<int> &a) {
    for (auto x : a) {
        out << x << " ";
    }
    return out;
}

bool cmp1(int a, int b) {
    return a > b;
}

namespace haizei {

class CMP {
public :
    CMP(int z = 0) : z(z) {} // z = 0 less,  z = 1 greater
    bool operator()(int a, int b) {
        return (a < b) ^ !!(z);
    }
    int z;
};

void sort(int *arr, int l, int r, function<bool(int, int)> cmp = CMP()) {
    if (l >= r) return ;
    int x = l, y = r, z = arr[(l + r) >> 1];
    do {
        while (cmp(arr[x], z)) ++x;
        while (cmp(z, arr[y])) --y;
        if (x <= y) {
            swap(arr[x], arr[y]);
            ++x, --y;
       }
    } while (x <= y);
    sort(arr, l, y, cmp);
    sort(arr, x, r, cmp);
    return ;
}

} // end of haizei

int main() {
    vector<int> arr;
    int n;
    cin >> n;
    while (n--) { int a; cin >> a, arr.push_back(a); }
    sort(arr.begin(), arr.end(), haizei::CMP(1));
    cout << arr << endl;
    int arr2[5] = {6, 8, 4, 5, 1};
    
    haizei::sort(arr2, 0, 4);
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    haizei::sort(arr2, 0, 4, cmp1);
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    haizei::sort(arr2, 0, 4);
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    haizei::sort(arr2, 0, 4, haizei::CMP(1));
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}
