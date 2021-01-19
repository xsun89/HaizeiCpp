//
// Created by Xin Sun on 2020-12-31.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <climits>

#define MAX_N 10005
using namespace std;
typedef struct Node {
    int max;
    int l, r;
}Node;

void update(Node *root, int ind){
    root[ind].max = max(root[ind << 1].max, root[ind << 1 | 1].max);
    return;
}
void buildSegmentTree(Node *root, int *data, int ind, int l, int r){
    if(root == NULL) return;
    root[ind].l = l;
    root[ind].r = r;
    if(l == r){
        root[ind].max = data[l];
        return;
    }
    int mid = (l + r) >> 1;
    buildSegmentTree(root, data, 2 * ind, l, mid);
    buildSegmentTree(root, data, 2 * ind + 1, mid + 1, r);
    update(root, ind);
}

void modify(Node *root, int ind, int k, int val){
    if(root[ind].l == root[ind].r){
        root[ind].max = val;
        return;
    }
    int mid = (root[ind].l + root[ind].r) >> 1;
    if(mid >= k) {
        modify(root, ind << 1, k, val);
    }else{
        modify(root, ind << 1 | 1, k, val);
    }
    update(root, ind);
    return;
}

int query(Node *root, int idx, int x, int y){
    if(root[idx].l >= x && root[idx].r <= y){
        return root[idx].max;
    }
    int ans = INT_MIN;
    int mid = (root[idx].l + root[idx].r) >> 1;
    if(x <= mid){
        ans = max(ans, query(root, idx << 1, x, y));
    }
    if(y > mid){
        ans = max(ans, query(root, idx << 1 | 1, x, y));
    }
    return ans;
}

int main()
{
    int n, m, a, b, c;
    scanf("%d%d", &n, &m);
    int data[MAX_N] = {0};
    for(int i = 1; i <= n; i++){
        scanf("%d", &data[i]);
    }
    Node *root = (Node *) malloc(sizeof(Node)*4*n);
    buildSegmentTree(root, data, 1, 1, n);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        switch (a) {
            case 1: modify(root, 1, b, c); break;
            case 2: {
                if (b > c) {
                    cout << "-2147483648" << endl;
                    break;
                }
                printf("%d\n", query(root, 1, b, c));
            } break;
        }
    }
    free(root);
    return 0;
}
