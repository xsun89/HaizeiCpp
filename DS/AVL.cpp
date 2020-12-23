//
// Created by Xin Sun on 2020-12-22.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
}Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL(){
    NIL->key = 0;
    NIL->h = 0;
    NIL->lchild = NIL;
    NIL->rchild = NIL;
    return;
}
Node *getNewNode(int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = val;
    node->h = 1;
    node->lchild = node->rchild = NIL;

    return node;
}

void clear(Node *root){
    if(root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
}
void update_height(Node *root){
    int h = root->lchild->h > root->rchild->h ? root->lchild->h : root->rchild->h;
    root->h = h + 1;

    return;
}
Node *left_rotate(Node *root){
    Node *node = root->rchild;
    root->rchild = node->lchild;
    node->lchild = root;
    update_height(root);
    update_height(node);
    return node;
}

Node *right_rotate(Node *root){
    Node *node = root->lchild;
    root->lchild = node->rchild;
    node->rchild = root;
    update_height(root);
    update_height(node);
    return node;
}
Node *maintain(Node *root){
    if(abs(root->lchild->h - root->rchild->h) <= 1) return root;

    if(root->lchild->h > root->rchild->h){
        if(root->lchild->lchild->h < root->lchild->rchild->h){
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    }else{
        if(root->rchild->rchild->h < root->rchild->lchild->h){
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}


Node *insert(Node *root, int val){
    if(root == NIL){
        root = getNewNode(val);
        return root;
    }
    if(root->key == val ) return root;
    if(root->key > val) {
        root->lchild = insert(root->lchild, val);
    }else{
        root->rchild = insert(root->rchild, val);
    }
    update_height(root);
    return maintain(root);
}

Node *predessor(Node *root){
    Node *node = root->lchild;
    while(node){
        node = node->rchild;
    }
    return node;
}



Node *erase(Node *root, int val){
    if(root == NIL) return root;
    if(root->key > val){
        root->lchild = erase(root->lchild, val);
    }else if(root->key < val){
        root->rchild = erase(root->rchild, val);
    }else{
        if(root->rchild == NIL || root->rchild == NIL){
            Node *node = root->lchild ? root->lchild : root->rchild;
            free(root);
            return node;
        }else{
            Node *node = predessor(root);
            root->key = node->key;
            root->lchild = erase(root->lchild, node->key);
        }
    }
    update_height(root);
    return maintain(root);
}
void print(Node *root) {
    printf("(%d[%d], %d, %d)\n",
           root->key, root->h,
           root->lchild->key,
           root->rchild->key
    );
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return ;
}
int main()
{
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 0: root = erase(root, val); break;
            case 1: root = insert(root, val); break;
        }
        output(root);
        printf("------------\n");
    }

    return 0;
}