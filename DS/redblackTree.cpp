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
    return;
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

void changeColor(Node *root){
    root->lchild->color = 1;
    root->rchild->color = 1;
    root->color = 0;
    return;
}

Node *left_rotate(Node *root){
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;

    return temp;

}

Node *right_rotate(Node *root){
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;

    return temp;
}
Node *insert_maintain(Node *root)
{
    if(root == NIL) return NIL;
    if(!hasRedChild(root)) return root;
    if(root->lchild->color == 0 && root->rchild->color == 0){
        changeColor(root);
        return root;
    }
    //从爷爷节点往下看
    if(root->lchild->color == 0 && hasRedChild(root->lchild)){
        if(root->lchild->rchild->color == 0){
            root->lchild = left_rotate(root->rchild);
        }
        root = right_rotate(root);
        changeColor(root);
    }else if(root->rchild->color == 0 && hasRedChild(root->rchild)) {
        if(root->rchild->lchild->color == 0){
            root->rchild = right_rotate(root->lchild);
        }
        root = left_rotate(root);
        changeColor(root);
    }
    return root;
}
Node *__insert(Node *root, int val){
    if(root == NIL) return getNewNode(val);
    if(root->key == val) return root;
    if(root->key > val){
        root->lchild = __insert(root->lchild, val);
    }else{
        root->rchild = __insert(root->rchild, val);
    }

    return insert_maintain(root);
}

Node *insert(Node *root, int val){
    root = __insert(root, val);
    root->color = 1;

    return root;
}
void print(Node *root) {
    printf("[%d]([%d], %d, %d)\n",
           root->color, root->key,
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
            //case 0: root = erase(root, val); break;
            case 1: root = insert(root, val); break;
        }
        output(root);
        printf("------------\n");
    }

    return 0;
}