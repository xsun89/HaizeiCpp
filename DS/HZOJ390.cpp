//
// Created by Xin Sun on 2021-01-08.
//

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 10000

int num[MAX_N];
int n, m, l, r;

int func(int x){
    int ret = 0;
    for(int i = 0; i < n; i++){
        ret += num[i] / x;
    }

    return ret;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
        r = max(r, num[i]);
    }
    while ( l != r)
    {
        int mid = (l + r + 1) >> 1;
        if(func(mid) >= m){
            l = mid;
        }else{
            r = mid - 1;
        }
    }

    cout << r << endl;
    return 0;
}