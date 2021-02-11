/*************************************************************************
	> File Name: 线段树3.cpp
	> Author: 王杨洋
	> Mail: 2549075913@qq.com
	> Created Time: 2021年01月02日 星期六 17时59分06秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
using namespace std;
#define MAX_NUM 100000

struct Node {
    Node() : tag(0), tag2(1), sum(0) {}
    long long sum, tag, tag2;
} tree[(MAX_NUM << 2) + 5];
long long arr[MAX_NUM];
long long p;

void update(long long ind) {
    tree[ind].sum = tree[ind << 1].sum + tree[ind << 1 | 1].sum;
    tree[ind].sum %= p;
    return ;
}

void build_tree(long long ind, long long l, long long r) {
    if (l == r) {
        tree[ind].sum = arr[l] % p;
        return ;
    }
    long long mid = (l + r) >> 1;
    build_tree(ind << 1, l, mid);
    build_tree(ind << 1 | 1, mid + 1, r);
    update(ind);
    return ;
}

void down(long long ind, long long l, long long r) {
    long long mid = (l + r) >> 1;
    if (tree[ind].tag) {
        tree[ind << 1].sum +=  (mid - l + 1) * tree[ind].tag;
        tree[ind << 1].sum %= p;
        tree[ind << 1].tag += tree[ind].tag;
        tree[ind << 1].tag %= p;
        tree[ind << 1 | 1].sum += (r - mid) * tree[ind].tag;
        tree[ind << 1 | 1].sum %= p;
        tree[ind << 1 | 1].tag += tree[ind].tag;
        tree[ind << 1 | 1].tag %= p;
        tree[ind].tag = 0;
    }
    return ;
}

void down2(long long ind, long long l, long long r) {
    long long mid = (l + r) >> 1;
    if (tree[ind].tag2 != 1) {
        tree[ind << 1].sum *= tree[ind].tag2;
        tree[ind << 1].sum %= p;
        tree[ind << 1].tag2 *= tree[ind].tag2;
        tree[ind << 1].tag2 %= p;
        tree[ind << 1].tag *= tree[ind].tag2;
        tree[ind << 1].tag %= p;
        tree[ind << 1 | 1].sum *= tree[ind].tag2;
        tree[ind << 1 | 1].sum %= p;
        tree[ind << 1 | 1].tag2 *= tree[ind].tag2;
        tree[ind << 1 | 1].tag2 %= p;
        tree[ind << 1 | 1].tag *= tree[ind].tag2;
        tree[ind << 1 | 1].tag %= p;
        tree[ind].tag2 = 1;
    }
    return ;
}

void modify(long long ind, long long l, long long r, long long b, long long c, long long d) {
    if (l >= b && r <= c) {
        tree[ind].sum += d * (r - l + 1);
        tree[ind].sum %= p;
        tree[ind].tag += d;
        tree[ind].tag %= p;
        return ;
    }
    down2(ind, l, r);
    down(ind, l, r);
    long long mid = (l + r) >> 1;
    if (b <= mid) modify(ind << 1, l, mid, b, c, d);
    if (c > mid) modify(ind << 1 | 1, mid + 1, r, b, c, d);
    update(ind);
    return;
}

void mult(long long ind, long long l, long long r, long long b, long long c, long long d) {
    if (l >= b && r <= c) {
        tree[ind].sum *= d;
        tree[ind].sum %= p;
        tree[ind].tag2 *= d;
        tree[ind].tag2 %= p;
        tree[ind].tag *= d;
        tree[ind].tag %= p;
        return ;
    }
    down2(ind, l, r);
    down(ind, l, r);
    long long mid = (l + r) >> 1;
    if (b <= mid) mult(ind << 1, l, mid, b, c, d);
    if (c > mid) mult(ind << 1 | 1, mid + 1, r, b, c, d);
    update(ind);
    return;
}

long long query(long long ind, long long l, long long r, long long b, long long c) {
    if (b <= l && r <= c) return tree[ind].sum;
    down2(ind, l, r);
    down(ind, l, r);
    long long mid = (l + r) >> 1;
    long long sum = 0;
    if (b <= mid) sum += query(ind << 1, l, mid, b, c);
    sum %= p;
    if (c > mid) sum += query(ind << 1 | 1, mid + 1, r, b, c);
    sum %= p;
    update(ind);
    return sum % p;
}

int main() {
    long long n, m, a, b, c, d;
    scanf("%lld%lld%lld", &n, &m, &p);
    for (long long i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    build_tree(1, 1, n);
    for (long long i =0; i < m; i++) {
        scanf("%lld%lld%lld",&a, &b, &c);
        switch (a) {
            case 1: {
                scanf("%lld", &d);
                mult(1, 1, n, b, c, d);
            } break;
            case 2: {
                scanf("%lld", &d);
                modify(1, 1, n, b, c, d);
            } break;
            case 3: {
                long long ans = query(1, 1, n, b, c);
                printf("%lld\n", ans);
            } break;
        }
    }
    return 0;
}
