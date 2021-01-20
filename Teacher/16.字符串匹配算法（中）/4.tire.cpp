/*************************************************************************
	> File Name: 4.tire.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26

typedef struct Node {
    int flag;
    struct Node *next[BASE];
} Node;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    memset(p->next, 0, sizeof(p->next));
    return p;
}

void insert(Node *p, const char *s) {
    for (int i = 0; s[i]; i++) {
        int ind = s[i] - 'a';
        if (p->next[ind] == NULL) p->next[ind] = getNewNode();
        p = p->next[ind];
    }
    p->flag = 1;
    return ;
}

void clear(Node *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

void output(Node *root, int k, char *s) {
    s[k] = 0;
    if (root->flag) {
        printf("%s\n", s);
    }
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        s[k] = 'a' + i;
        output(root->next[i], k + 1, s);
    }
    return ;
}

int main() {
    int n;
    char str[100];
    scanf("%d", &n);
    Node *root = getNewNode();
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(root, str);
    }
    output(root, 0, str);
    clear(root);
    return 0;
}
