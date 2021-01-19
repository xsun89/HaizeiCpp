//
// Created by Xin Sun on 2021-01-06.
//

#include <iostream>

using namespace std;

#define MAX_N 1000000
int arr[MAX_N + 5];
int dp[MAX_N + 5];
int main()
{
    int ans = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    dp[0] = 1;
    for (int i = 0; i < n; i++){
        dp[i] = 1;
        for (int j = 0; j < i; j++){
            if(arr[j] < arr [i]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }

    cout << ans << endl;
}