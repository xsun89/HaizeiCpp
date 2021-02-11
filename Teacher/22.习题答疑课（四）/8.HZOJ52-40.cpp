#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=1000005;
long long dp[maxn], sum[maxn], f[maxn], q[maxn];
int n,m;
int head=0,tail=0;
void set(int a,int b)
{
    dp[a]=dp[b]+(sum[a]-sum[b])*(sum[a]-sum[b])+m;
    f[a]=dp[a]+sum[a]*sum[a];
    return ;
}
double slope(int a,int b)
{
    return 1.0*(f[a]-f[b])/(sum[a]-sum[b]);
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>sum[i];
        sum[i]+=sum[i-1];
    }
    q[tail++]=0;
    q[tail++]=1;
    set(1,0);
    for(int i=2;i<=n;i++)
    {
        while(tail-head>=2&&slope(q[head],q[head+1])<=sum[i]*2) head+=1;
        set(i,q[head]);
        while(tail-head>=2&&slope(q[tail-1],q[tail-2])>slope(q[tail-1],i)) tail-=1;
        q[tail++]=i;
    }
    cout << dp[n] << endl;
    return 0;
}
