//
// Created by Xin Sun on 2021-01-08.
//

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
#define MAX_N 100000
#define MAX_K 1000000005

typedef struct Node {
    int num, cnt;
}Node;

bool cmp(const Node& a, const Node& b)
{
    return a.num < b.num;
}

Node wm[MAX_N + 5];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++){
        scanf("%d", &wm[i].num);
        wm[i].cnt = i + 1;
    }
    wm[n].num = MAX_K;
    wm[n].cnt = 0;
    n++;
    sort(wm, wm + n, cmp);

    for(int i = 0; i < m; i++){
        int t, l = 0, r = n -1;
        scanf("%d", &t);
        while(l != r){
            int mid = (l + r) >> 1;
            if(wm[mid].num >= t){
                r = mid;
            }else{
                l = mid + 1;
            }
        }

        printf("%d\n", wm[l].cnt);


    }
    return 0;
}