/*************************************************************************
*File Name   : 224.cpp
*Author      : Zsl
*mail        : zsl_hfut@163.com
*Created Time: Mon 04 Jan 2021 05:40:22 PM CST
*************************************************************************/
#include <iostream>
#include <cstdio>
#include <list>
using namespace std;

#define MAX_N 100000

typedef class options{
public:
    options(long long _op, long long _val) {
        op = _op;
        val = _val;
    }
    long long op;//0:+ 1:*
    long long val;
}options;

typedef class Node{
public:
    long long data;
    list<options> opt;
}Node;
Node SegmentTree[MAX_N << 2];
long long N, M, P;

void update(long long index) {
    SegmentTree[index].data = (SegmentTree[index << 1].data + SegmentTree[index << 1 | 1].data) % P;
    return;
}

void down(long long index, long long l, long long r) {
    long long mid = (l + r) >> 1;
    while(!SegmentTree[index].opt.empty()) {
        options op = SegmentTree[index].opt.front();
        SegmentTree[index << 1].opt.push_back(op);
        SegmentTree[index << 1 | 1].opt.push_back(op);
        if(op.op == 0){
            SegmentTree[index << 1].data += ((mid - l + 1) * op.val);
            SegmentTree[index << 1 | 1].data += ((r - mid) * op.val);
        } else {
            SegmentTree[index << 1].data *= op.val;
            SegmentTree[index << 1 | 1].data *= op.val;
        }
        SegmentTree[index << 1].data %= P;
        SegmentTree[index << 1 | 1].data %= P;
        SegmentTree[index].opt.pop_front();
    }
}

void build_tree(long long index, long long l, long long r){
    if(l == r){
        scanf("%lld", &SegmentTree[index].data);
        return;
    }
    long long mid = (l + r) >> 1;
    build_tree(index << 1, l, mid);
    build_tree(index << 1 |1, mid + 1, r);
    update(index);
    return;
}

long long output(long long index, long long l, long long r, long long x, long long y){
    long long ret = 0;
    if(l >= x && r <= y) {
        ret = SegmentTree[index].data;
        return ret;
    }
    down(index, l, r);
    long long mid = (l + r) >> 1;
    if(mid >= x){
        ret += output(index << 1, l, mid, x, y);
    }
    ret %= P;
    if(mid < y){
        ret += output(index << 1 | 1, mid + 1, r, x, y);
    }
    ret %= P;
    return ret;
}

void add(long long index, long long l, long long r, long long x, long long y, long long k) {
    if(l >= x && r <= y) {
        SegmentTree[index].opt.push_back({0, k});
        SegmentTree[index].data += ((r - l + 1) * k);
        SegmentTree[index].data %= P;
        return;
    }
    down(index, l, r);
    long long mid = (l + r) >> 1;
    if(mid >= x){
        add(index << 1, l, mid, x, y, k);
    }
    if(mid < y){
        add(index << 1 | 1, mid + 1, r, x, y, k);
    }
    update(index);
}

void multiply(long long index, long long l, long long r, long long x, long long y, long long k) {
    if(l >= x && r <= y) {
        SegmentTree[index].opt.push_back({1, k});
        SegmentTree[index].data *= k;
        SegmentTree[index].data %= P;
        return;
    }
    down(index, l, r);
    long long mid = (l + r) >> 1;
    if(mid >= x){
        multiply(index << 1, l, mid, x, y, k);
    }
    if(mid < y){
        multiply(index << 1 | 1, mid + 1, r, x, y, k);
    }
    update(index);
    return;
}

int main() {
    scanf("%lld%lld%lld", &N, &M, &P);
    build_tree(1, 1, N);

    long long op, x, y, k;
    for(long long i = 0; i < M; ++i) {
        scanf("%lld%lld%lld", &op, &x, &y);
        switch(op){
            case 1:{
                scanf("%lld", &k);
                multiply(1, 1, N, x, y, k);
                break;
            }
            case 2:{
                scanf("%lld", &k);
                add(1, 1, N, x, y, k);
                break;
            }
            case 3:{
                printf("%lld\n",output(1, 1, N, x, y) % P);
                break;
            }
        }
    }
    return 0;
}
