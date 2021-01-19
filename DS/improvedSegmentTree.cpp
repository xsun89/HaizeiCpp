//
// Created by Xin Sun on 2021-01-02.
//

#include <iostream>
#include <cstdio>

using namespace std;
#define MAX_N 10000
long long data[MAX_N];
typedef struct Node {
    long long sum;
    long long tag;
}Node;
int flag = 1;
void update(Node *root, long long ind){
    root[ind].sum = root[ind << 1].sum + root[ind << 1 | 1].sum;

    return;
}
void printSegmentTree(Node *root, long long ind, long long l, long long r){
    if(l == r){
        flag && printf("tree : ind=%lld, l=%lld, r=%lld, sum=%lld, tag=%lld\n",
                       ind, l, r, root[ind].sum, root[ind].tag);
        return;
    }
    flag && printf("tree : ind=%lld, l=%lld, r=%lld, sum=%lld, tag=%lld\n",
                   ind, l, r, root[ind].sum, root[ind].tag);
    long long mid = (l + r) >> 1;
    printSegmentTree(root,  ind << 1, l, mid);
    printSegmentTree(root, ind << 1 | 1, mid + 1, r);
}
void down(Node *root, long long ind, long long l, long long r)
{
    printf("down\n");
    printSegmentTree(root, ind, l, r);
    if(root[ind].tag != 0){
        long long mid = (l + r) >> 1;
        long long val = root[ind].tag;
        root[ind << 1].sum += val * (mid - l + 1);
        root[ind << 1].tag += val;
        root[ind << 1 | 1].tag += val;
        root[ind << 1 | 1].sum += val * (r - mid);
        root[ind].tag = 0;
    }
    return;
}
void buildSegmentTree(Node *root, long long *data, long long ind, long long l, long long r){
    if(l == r){
        root[ind].sum = data[l];
        return;
    }
    long long mid = (l + r) >> 1;
    buildSegmentTree(root, data, ind << 1, l, mid);
    buildSegmentTree(root, data, ind << 1 | 1, mid + 1, r);
    update(root, ind);
}



void modify(Node *root, long long ind, long long l, long long r, long long x, long long y, long long val){
    printf("modify\n");
    printSegmentTree(root, ind, l, r);
    if(x <= l && y >= r){
        root[ind].sum += val * (r - l + 1);
        root[ind].tag += val;
        return;
    }
    down(root, ind, l, r);
    long long mid = (l + r) >> 1;

    if(x <= mid){
        modify(root, ind << 1, l, mid, x, y, val);
    }
    if(y > mid){
        modify(root, ind << 1 | 1, mid + 1, r, x, y, val);
    }

    update(root, ind);
}

long long query(Node *root, int ind, int l, int r, long long x, long long y)
{
    printf("query\n");
    printSegmentTree(root, ind, l, r);
    if(x <= l && y >= r){
        return root[ind].sum;
    }
    down(root, ind, l, r);
    long long mid = (l + r) >> 1;
    long long ans = 0;
    if(x <= mid){
        ans += query(root, ind << 1, l, mid, x, y);
    }
    if(y > mid){
        ans += query(root, ind << 1 | 1, mid + 1, r, x, y);
    }
    return ans;
}

int main()
{
    long long n, m;
    scanf("%lld%lld", &n, &m);
    for (long long i = 1; i <= n; i++){
        scanf("%lld", &data[i]);
    }

    Node *nodes = (Node *) malloc(sizeof(Node) * 4 * n);
    buildSegmentTree(nodes, data, 1, 1, n);
    long long a, b, c, d;
    for (int i = 0; i < m; i++){
        scanf("%lld%lld%lld", &a, &b, &c);
        switch(a){
            case 1:{
                scanf("%lld", &d);
                modify(nodes, 1, 1, n, b, c, d);
                printSegmentTree(nodes, 1, 1, n);
                break;
            }
            case 2:{
                if (b > c) {
                    printf("0\n");
                    break;
                }
                printf("%lld\n", query(nodes, 1, 1, n, b, c));
                printSegmentTree(nodes, 1, 1, n);
            } break;
        }
    }
    free(nodes);
    return 0;
}