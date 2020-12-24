//
// Created by Xin Sun on 2020-12-23.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int key;
    int color; //0:red 1:black 2:
    struct Node *lchild, *rchild;
}Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL(){
    NIL->key = 0;
    NIL->color = 1;
    NIL->lchild = NIL->rchild = NIL;
}

Node *getNewNode(int val){
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = val;
    node->color = 0;
    node->lchild = node->rchild = NIL;

    return node;
}

void clear(Node *root){
    if(root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);

    return;
}

int hasRedChild(Node *root){
    if(root->lchild->color == 0 || root->rchild->color == 0){
        return 1;
    }else{
        return 0;
    }
}
Node *insert_maintain(Node *root)
{
    if(root == NIL) return NIL;
    if(!hasRedChild(root)) return root;
    if(root->lchild->color == 0 && root->rchild->color == 0){
        root->lchild->color = 1;
        root->rchild->color = 1;
        root->color = 0;
    }
    int flag = 0;
    //从爷爷节点往下看
    if(root->lchild->color == 0 && hasRedChild(root->lchild)){
        flag = 1;
    }else if(root->rchild->color == 0 && hasRedChild(root->rchild)){
        flag = 2;
    }



    return root;
}
Node *__insert(Node *root, int val){
    if(root == NIL) return getNewNode(val);
    if(root->key == val) return root;
    if(root->key > val){
        root->lchild = insert(root->lchild, val);
    }else{
        root->rchild = insert(root->rchild, val);
    }

    return insert_maintain(root);
}

Node *insert(Node *root, int val){
    root = __insert(root, val);
    root->color = 1;

    return root;
}
int main()
{
    return 0;
}
