//
// Created by Xin Sun on 2021-01-06.
//

#include <iostream>

using namespace std;

#define MAX_N 1000000
int arr[MAX_N + 5];
int len[MAX_N + 5];
int dp[MAX_N + 5];

int binary_search(int *arr, int n, int x)
{
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if(arr[mid] < x){
            head = mid + 1;
        } else{
            tail = mid;
        }
    }
    return head;
}
int main()
{
    int ans = 0;
    int n;
    cin >> n;
    memset(len, 0x3f, sizeof(len));
    len[0] = 0;

    for (int i = 1; i <= n; i++){
        cin >> arr[i];
    }
    dp[1] = 1;
    for (int i = 1; i <= n; i++){
        dp[i] = binary_search(len, ans + 1, arr[i]);
        len[dp[i]] = arr[i];
        ans = max(ans, dp[i]);
    }

    cout << ans << endl;
}