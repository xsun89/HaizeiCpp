//
// Created by Xin Sun on 2020-12-30.
//

#include <stdio.h>
#include <stdlib.h>

#define swap(a, b){ \
    __typeof(a) __c;\
    __c = a;        \
    a = b;          \
    b = __c;        \
}

typedef struct Node{
    char ch;
    double p;
    struct Node *lchild, *rchild;
}Node; //

typedef struct HuffmanTree{
    Node *root;
}HuffmanTree;

Node *getNewNode(char ch, double per){
    Node *node = (Node *)malloc(sizeof(Node));
    node->ch = ch;
    node->p = per;
    node->lchild = NULL;
    node->rchild = NULL;

    return node;
}

void clearNode(Node *node){
    if(node == NULL) return;
    clearNode(node->lchild);
    clearNode(node->rchild);
    free(node);

    return;
}

void clear(HuffmanTree *tree)
{
    if(tree == NULL) return;
    clearNode(tree->root);
    free(tree);

    return;
}

Node *combineNode(Node *a, Node *b){
    Node *node = getNewNode('$', a->p + b->p);
    node->lchild = a;
    node->rchild = b;

    return node;
}

HuffmanTree *getHaffManTree()
{
    HuffmanTree *tree = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    tree->root = NULL;
    return tree;
}

void minNode(Node **nodes, int n){
    for(int i = n - 1; i >= 0; i--){
        if(nodes[n]->p > nodes[i]->p){
            swap(nodes[n], nodes[i]);
        }
    }
    return;
}

void buildHuffmanTree(HuffmanTree *tree, Node **nodes, int n){
    for (int i = 1; i < n; i++){
        minNode(nodes, n - i);
        minNode(nodes, n - i - 1);

        nodes[n - i - 1] = combineNode(nodes[n - i], nodes[n - i -1]);
    }
    tree->root = nodes[0];
    return;
}

void _outputHuffmanTree(Node *root, char* str, int k){
    if(root->lchild == NULL && root->rchild == NULL){
        printf("%c %s\n", root->ch, str);
        return;
    }
    str[k] = '0';
    _outputHuffmanTree(root->lchild, str, k + 1);
    str[k] = '1';
    _outputHuffmanTree(root->rchild, str, k + 1);

    return;
}

void output_encode(Node *root){
    char str[100] = {0};
    _outputHuffmanTree(root, str, 0);
    return;
}

void print(Node *root)
{
    printf("%c %lf\n",
           root->ch, root->p);
    return ;
}



void pre_order(Node *root){
    if(root == NULL) return;

    print(root);
    pre_order(root->lchild);
    pre_order(root->rchild);
}
void output(HuffmanTree *tree){
    if(tree == NULL) return;
    pre_order(tree->root);
}

int main(){
    int n;
    scanf("%d", &n);
    Node **nodes = (Node **)malloc(sizeof(Node *)*n);

    for(int i = 0; i<n; i++){
        char ct[2];
        double pt;
        scanf("%s%lf", ct, &pt);
        nodes[i] = getNewNode(ct[0], pt);
    }

    HuffmanTree *tree = getHaffManTree();
    buildHuffmanTree(tree, nodes, n);
    output_encode(tree->root);
    output(tree);
    clear(tree);
    free(nodes);

    return 0;
}