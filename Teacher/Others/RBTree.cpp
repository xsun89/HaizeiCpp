#include <stdio.h>
#include <stdlib.h>
#define L(a) a->lchild
#define R(a) a->rchild

typedef struct Node {
    int key, color;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
void initNIL() {
    NIL->key = 0;
    NIL->color = 1;
    L(NIL) = R(NIL) = NIL;
    return ;
}

Node *getNewNode(int key) {
    // p?
    Node *root = (Node *)malloc(sizeof(Node));
    root->key = key;
    root->color = 0;
    L(root) = R(root) = NIL;
    return root;
}

int has_red_child(Node *root) {
    return L(root)->color == 0 || R(root)->color == 0;
}

Node *l_rotate(Node *root) {
    Node *temp = R(root);
    R(root) = L(temp);
    L(temp) = root;
    return temp;
}

Node *r_rotate(Node *root) {
    Node *temp = L(root);
    L(root) = R(temp);
    R(temp) = root;
    return temp;
}

Node *insert_maintain(Node *root) {
    if (!has_red_child(root)) return root;
    int flag = 0;
    if (L(root)->color == 0 && has_red_child(L(root))) flag = 1;  // attention! left tree conflict
    if (R(root)->color == 0 && has_red_child(R(root))) flag = 2;
    if (flag == 0) return root;
    if (L(root)->color == 0 && R(root)->color == 0) {
        root->color = 0;
        L(root)->color = R(root)->color = 1;
        return root;
    }
    // LR LL
    if (flag == 1) {
        if (R(L(root)) == 0) {
            L(root) = l_rotate(L(root));
        }
        root = r_rotate(root);
    } else {
    // RL RR
        if (L(R(root)) == 0) {
            R(root) = r_rotate(R(root));
        }
        root = l_rotate(root);
    }
    // root->color?
    root->color = 0;
    L(root)->color = R(root)->color = 1;
    return root;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (key > root->key) R(root) = __insert(R(root), key);
    else L(root) = __insert(L(root), key);
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = 1;
    return root;
}

Node *pre(Node *root) {
    Node *temp = L(root);
    while (R(temp) != NIL) temp = R(temp);
    return temp;
}

Node *erase_maintain(Node *root) {
    if (L(root)->color != 2 && R(root)->color != 2) return root;
    if (has_red_child(root)) {
        int flag = 0;
        root->color = 0;  // original red
        if (root->lchild->color == 0) {
            root = r_rotate(root);
            flag = 1;
        } else {
            root = l_rotate(root);
            flag = 2;
        }
        root->color = 1;  // new root black
        if (flag == 1) root->rchild = erase_maintain(root->rchild);
        else root->lchild = erase_maintain(root->lchild);
        return root;
    }
    // spacial red brother  (can merge)
    /*
    if (L(root)->color == 0) {
        root->color = 0;
        root = r_rotate(root);  // rotate return !!
        root->color = 1;
        R(root) = erase_maintain(R(root));
        return root;
        // must return?? go ahead??
    } else if (R(root)->color == 0){
        root->color = 0;
        root = l_rotate(root);
        root->color = 1;
        L(root) = erase_maintain(L(root));
        return root;
    }
    */
    // case 1 black brother child
    if (L(root)->color == 2 && !has_red_child(R(root)) ||
        R(root)->color == 2 && !has_red_child(L(root))) {
            root->color += 1;
            L(root)->color -= 1;
            R(root)->color -= 1;
            return root;
        }
    // case 2 RL RR
    if (L(root)->color == 2) {
        L(root)->color -= 1;
        if (R(R(root)) != 0) {
            R(root)->color = 0;
            R(root) = r_rotate(R(root));
            R(root)->color = 1;
        }
        root = l_rotate(root);
        root->color = L(root)->color;
    } else {
    // case 3 LR LL
        R(root)->color -= 1;
        if (L(L(root)) != 0) {
            L(root)->color = 0;
            L(root) = l_rotate(L(root));
            L(root)->color = 1;
        }
        root = r_rotate(root);
        root->color = R(root)->color;
    }
    L(root)->color = R(root)->color = 1;
    return root;
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return NIL;
    if (key > root->key) {
        R(root) = __erase(R(root), key);
    } else if (key < root->key) {
        L(root) = __erase(L(root), key);
    } else {
        if (L(root) == NIL || R(root) == NIL) {
            Node *temp = L(root) != NIL ? L(root) : R(root);
            temp->color += root->color;  // correct!
            free(root);
            return temp;
        } else {
            Node *temp = pre(root);
            root->key = temp->key;
            L(root) = __erase(L(root), temp->key);
        }
    }
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    root->color = 1;
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(L(root));
    clear(R(root));
    free(root);
    return ;
}

void print(Node *root) {
    printf("%d %d %d %d\n", root->key, root->color, L(root)->key, R(root)->key);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    output(L(root));
    print(root);
    output(R(root));
    return ;
}

int main() {
    int x, y;
    initNIL();
    Node *root = NIL;
    while (~scanf("%d%d", &x, &y)) {
        switch (x) {
            case 1: root = insert(root, y); break;
            case 2: root = erase(root, y); break;
            case 3: output(root); break;
        }
    }
    clear(root);
    return 0;
}