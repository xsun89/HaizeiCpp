/*************************************************************************
	> File Name: 线段树3.cpp
	> Author: 王杨洋
	> Mail: 2549075913@qq.com
	> Created Time: 2021年01月02日 星期六 17时59分06秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
using namespace std;
#define MAX_NUM 20000

struct Node {
    int sum, tag, tag2 = 1;
} tree[MAX_NUM << 2 | 1];
int arr[MAX_NUM];
int p;

void update(int ind) {
    tree[ind].sum = tree[ind << 1].sum + tree[ind << 1 | 1].sum;
    tree[ind].sum %= p;
    return ;
}

void build_tree(int ind, int l, int r) {
    if (l == r) {
        tree[ind].sum = arr[l] % p;
        return ;
    }
    int mid = (l + r) >> 1;
    build_tree(ind << 1, l, mid);
    build_tree(ind << 1 | 1, mid + 1, r);
    update(ind);
    return ;
}

void down(int ind, int l, int r) {
    if (l == r) return ;
    int mid = (l + r) >> 1;
        if (tree[ind].tag) {
            tree[ind << 1].sum +=  (mid - l + 1) * tree[ind].tag;
            tree[ind << 1].sum %= p;
            tree[ind << 1].tag += tree[ind].tag;
            tree[ind << 1 | 1].sum += (r - mid) * tree[ind].tag;
            tree[ind << 1 | 1].sum %= p;
            tree[ind << 1 | 1].tag += tree[ind].tag;
            tree[ind].tag = 0;
        }
    down(ind << 1, l, mid);
    down(ind << 1 | 1, mid + 1, r);
    return ;
}

void down2(int ind, int l, int r) {
    if (l == r) return ;
    int mid = (l + r) >> 1;
    if (tree[ind].tag2 != 1) {
        tree[ind << 1].sum *= tree[ind].tag2;
        tree[ind << 1].sum %= p;
        tree[ind << 1].tag2 *= tree[ind].tag2;
        tree[ind << 1 | 1].sum *= tree[ind].tag2;
        tree[ind << 1 | 1].sum %= p;
        tree[ind << 1 | 1].tag2 *= tree[ind].tag2;
        tree[ind].tag2 = 1;
    }
    down2(ind << 1, l, mid);
    down2(ind << 1 | 1, mid + 1, r);
    return ;
}

void modify(int ind, int l, int r, int b, int c, int d) {
    if (l >= b && r <= c) {
        tree[ind].sum += d * (r - l + 1);
        tree[ind].sum %= p;
        tree[ind].tag += d;
        down(ind, l, r);
        return ;
    }
    int mid = (l + r) >> 1;
    if (b <= mid) modify(ind << 1, l, mid, b, c, d);
    if (c > mid) modify(ind << 1 | 1, mid + 1, r, b, c, d);
    update(ind);
    return;
}

void mult(int ind, int l, int r, int b, int c, int d) {
    if (l >= b && r <= c) {
        tree[ind].sum *= d;
        tree[ind].sum %= p;
        tree[ind].tag2 *= d;
        down2(ind, l, r);
        return ;
    }
    int mid = (l + r) >> 1;
    if (b <= mid) mult(ind << 1, l, mid, b, c, d);
    if (c > mid) mult(ind << 1 | 1, mid + 1, r, b, c, d);
    update(ind);
    return;
}

int query(int ind, int l, int r, int b, int c) {
    if (b <= l && r <= c) return tree[ind].sum;
    //down(ind, l, r);
    int mid = (l + r) >> 1;
    int sum = 0;
    if (b <= mid) sum += query(ind << 1, l, mid, b, c);
    if (c > mid) sum += query(ind << 1 | 1, mid + 1, r, b, c);
    return sum % p;
}

int main() {
    int n, m, a, b, c, d;
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }
    build_tree(1, 1, n);
    for (int i =0; i < m; i++) {
        scanf("%d%d%d",&a, &b, &c);
        switch (a) {
            case 1: {
                scanf("%d", &d);
                mult(1, 1, n, b, c, d);
            } break;
            case 2: {
                scanf("%d", &d);
                modify(1, 1, n, b, c, d);
            } break;
            case 3: {
                int ans = query(1, 1, n, b, c);
                printf("%d\n", ans);
            } break;
        }
    }
    return 0;
}
