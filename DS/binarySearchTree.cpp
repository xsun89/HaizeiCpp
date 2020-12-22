//
// Created by Xin Sun on 2020-12-20.
//
#include <stdio.h>
#include <stdlib.h>
#define KEY(n) (n ? n->key : 0)
typedef struct Node {
    int key;
    struct Node *lchild;
    struct Node *rchild;
}Node;

typedef struct SearchTree{
    Node *root;
    int n;
}SearchTree;

Node *getNewNode(int val){
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = val;
    node->lchild = node->rchild = NULL;
    return node;
}

SearchTree *getSearchTree()
{
    SearchTree *tree = (SearchTree *)malloc(sizeof(SearchTree));
    tree->root = NULL;
    tree->n = 0;

    return tree;
}

Node *insertNode(Node *root, int val){
    if(root == NULL){
        root = getNewNode(val);
        return root;
    }

    if(val > root->key){
        root->rchild = insertNode(root->rchild, val);
    } else {
        root->lchild = insertNode(root->lchild, val);
    }
    return root;
}

void insert(SearchTree *tree, int val){
    tree->root = insertNode(tree->root, val);
    tree->n++;
    return;
}

Node *searchNode(Node *root, int val){
    if(root == NULL) return NULL;
    if(root->key == val){
        return root;
    }
    if(val > root->key){
        return searchNode(root->rchild, val);
    }else if(val < root->key){
        return searchNode(root->lchild, val);
    }
}

Node *search(SearchTree *tree, int val){
    Node *node = searchNode(tree->root, val);
    return node;
}
void clearNode(Node *node){
    if(node == NULL) return;
    clearNode(node->lchild);
    clearNode(node->rchild);
    free(node);
    return;
}

void clear(SearchTree *tree)
{
    if(tree == NULL) return;
    clearNode(tree->root);
    free(tree);

    return;
}

Node *predessor(Node *root){
    Node *tmpNode = root->lchild;
    while(tmpNode != NULL){
        tmpNode = tmpNode->rchild;
    }
    return tmpNode;
}
Node *eraseNode(Node *root, int val){
    if(root == NULL) return root;
    if(val > root->key){
        root->rchild = eraseNode(root->rchild, val);
    }else if(val < root->key){
        root->lchild = eraseNode(root->lchild, val);
    }else{
        if(root->lchild == NULL || root->rchild == NULL){
            Node *node = root->lchild ? root->lchild :  root->rchild;
            free(root);
            return node;
        }else{
            Node *node = predessor(root);
            root->key = node->key;
            root->lchild = eraseNode(root->lchild, node->key);
        }
    }

    return root;
}

void erase(SearchTree *tree, int val){
    tree->root = eraseNode(tree->root, val);
    tree->n--;
    return;
}

void print(Node *root)
{
    printf("(%d, %d, %d)\n",
           KEY(root),
           KEY(root->lchild), KEY(root->rchild)
    );
    return ;
}

void in_order(Node *root){
    if(root == NULL) return;
    in_order(root->lchild);
    print(root);
    in_order(root->rchild);
}
void output(SearchTree *tree){
    if(tree == NULL) return;
    in_order(tree->root);
}
int main()
{
    int op, val;
    SearchTree *tree = getSearchTree();
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 0: {
                Node *node = search(tree, val);
                int ret = 0;
                if (node != NULL) {
                    ret = 1;
                }
                printf("search %d, result : %d\n", val, ret);
                break;
            }
            case 1:
                insert(tree, val);
                break;
            case 2:
                erase(tree, val);
                break;
        }
        if (op == 1 || op == 2) {
            output(tree);
            printf("------------\n");
        }
    }
    return 0;
}