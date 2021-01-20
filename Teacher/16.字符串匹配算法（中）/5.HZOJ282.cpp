/*************************************************************************
	> File Name: 5.HZOJ282.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define MAX_N 100000
#define BASE 31
struct node {
    node *next[2];
} tree[MAX_N * BASE+ 5];
int cnt = 0;
node *getNode() {
    return &tree[cnt++];
}

void insert(node *root, int x) {
    for (int i = 30; i >= 0; i--) {
        int ind = !!(x & (1 << i));
        if (root->next[ind] == NULL) root->next[ind] = getNode();
        root = root->next[ind];
    }
    return ;
}

int query(node *root, int x) {
    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        int ind = !(x & (1 << i));
        if (root->next[ind]) {
            ans |= (1 << i);
            root = root->next[ind];
        } else {
            root = root->next[!ind];
        }
    }
    return ans;
}

int n;
int val[MAX_N + 5];

int main() {
    cin >> n;
    int ans = 0, a;
    node *root = getNode();
    cin >> a, n--;
    insert(root, a);
    while (n--) {
        cin >> a;
        ans = max(query(root, a), ans);
        insert(root, a);
    }
    cout << ans << endl;
    return 0;
}
