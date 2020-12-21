//
// Created by Xin Sun on 2020-12-20.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *lchild;
    struct Node *rchild;
}Node;

typedef struct SearchTree{
    Node *head;
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
    tree->head = NULL;
    tree->n = 0;

    return tree;
}

void insertNode(Node *root, int val){
    if(root == NULL){
        root = getNewNode(val);
        return;
    }

    if(val > root->key){
        insertNode(root->rchild, val);
    } else {
        insertNode(root->lchild, val);
    }
    return;
}

void insert(SearchTree *tree, int val){
    insertNode(tree->head, val);
    tree->n++;
    return;
}

Node *searchNode(Node *root, int val){
    if(root == NULL) return NULL;
    if(root->key == val){
        return root;
    }
    if(val > root->key){
        searchNode(root->rchild, val);
    }else if(val < root->key){
        searchNode(root->lchild, val);
    }
}

Node *search(SearchTree *tree, int val){
    Node *node = searchNode(tree->head, val);
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
    clearNode(tree->head);
    free(tree);

    return;
}
void removeNode(Node *root){
    if(root == NULL) return;
    if(root ->lchild == NULL && root->rchild == NULL){
        clearNode(root);
        return;
    }
    if(root ->rchild != NULL && root->lchild == NULL){
        root->key = root ->rchild->key;
        removeNode(root ->rchild);
        return;
    }
    if(root ->rchild == NULL && root->lchild != NULL){
        root->key = root ->lchild->key;
        removeNode(root ->lchild);
        return;
    }


}
void remove(SearchTree *tree, int val){
    Node *node = search(tree, val);
    if(node != NULL) {
        removeNode(node, val);
        tree->n--;
    }
    return;
}

int main()
{
    return 0;
}