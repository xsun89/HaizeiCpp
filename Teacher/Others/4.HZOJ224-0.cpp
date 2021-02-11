/*************************************************************************
*File Name   : 224.cpp
*Author      : Zsl
*mail        : zsl_hfut@163.com
*Created Time: Mon 04 Jan 2021 05:40:22 PM CST
*************************************************************************/
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

#define MAX_N 100000


typedef class options{
public:
    options(int _op, int _val) {
        op = _op;
        val = _val;
    }
    int op;//0:+ 1:*
    int val;
}options;

typedef class Node{
public:
    int data;
    queue<options> opt;
}Node;
Node SegmentTree[MAX_N << 2];
int N, M, P;

void update(int index) {
    SegmentTree[index].data = (SegmentTree[index << 1].data + SegmentTree[index << 1 | 1].data) % P;
    return;
}

void down(int index, int l, int r) {
    int mid = (l + r) >> 1;
    while(!SegmentTree[index].opt.empty()) {
        options op = SegmentTree[index].opt.front();
        SegmentTree[index << 1].opt.push(op);
        SegmentTree[index << 1 | 1].opt.push(op);
        if(op.op == 0){
            SegmentTree[index << 1].data += ((mid - l + 1) * op.val);
            SegmentTree[index << 1 | 1].data += ((r - mid) * op.val);
        } else {
            SegmentTree[index << 1].data *= op.val;
            SegmentTree[index << 1 | 1].data *= op.val;
        }
        SegmentTree[index << 1].data %= P;
        SegmentTree[index << 1 | 1].data %= P;
        SegmentTree[index].opt.pop();
    }
}

void build_tree(int index, int l, int r){
    if(l == r){
        scanf("%d", &SegmentTree[index].data);
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(index << 1, l, mid);
    build_tree(index << 1 |1, mid + 1, r);
    update(index);
    return;
}

int output(int index, int l, int r, int x, int y){
    int ret = 0;
    if(l >= x && r <= y) {
        ret = SegmentTree[index].data;
        return ret;
    }
    down(index, l, r);
    int mid = (l + r) >> 1;
    if(mid >= x){
        ret += output(index << 1, l, mid, x, y);
    }
    if(mid < y){
        ret += output(index << 1 | 1, mid + 1, r, x, y);
    }
    return ret;
}

void add(int index, int l, int r, int x, int y, int k) {
    if(l >= x && r <= y) {
        SegmentTree[index].opt.push({0, k});
        SegmentTree[index].data += ((r - l + 1) * k);
        SegmentTree[index].data %= P;
        return;
    }
    down(index, l, r);
    int mid = (l + r) >> 1;
    if(mid >= x){
        add(index << 1, l, mid, x, y, k);
    }
    if(mid < y){
        add(index << 1 | 1, mid + 1, r, x, y, k);
    }
    update(index);
}

void multiply(int index, int l, int r, int x, int y, int k) {
    if(l >= x && r <= y) {
        SegmentTree[index].opt.push({1, k});
        SegmentTree[index].data *= k;
        SegmentTree[index].data %= P;
        return;
    }
    down(index, l, r);
    int mid = (l + r) >> 1;
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
    scanf("%d%d%d", &N, &M, &P);
    build_tree(1, 1, N);

    int op, x, y, k;
    for(int i = 0; i < M; ++i) {
        scanf("%d%d%d", &op, &x, &y);
        switch(op){
            case 1:{
                scanf("%d", &k);
                multiply(1, 1, N, x, y, k);
                break;
            }
            case 2:{
                scanf("%d", &k);
                add(1, 1, N, x, y, k);
                break;
            }
            case 3:{
                printf("%d\n",output(1, 1, N, x, y) % P);
                break;
            }
        }
#if 0
        for(int i = 1; i < (N << 2); ++i) {
            printf("%d ",SegmentTree[i].data);
        }
#endif
    }


    return 0;
}
