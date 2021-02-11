/*************************************************************************
	> File Name: 1.HZOJ64-0.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
using namespace std;

// 胡医生说：指标合格
typedef struct Node{
	int key;
	int color; // 0为red 1为black 2为双黑
	struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)

// 胡医生说：需要住院治疗
//__attribute__((constructor))
void init_NIL() {
	NIL->key = 0;
	NIL->color = 1;
	NIL->lchild = NIL->rchild = NIL;
	return;
}

// 胡医生说：指标合格
Node *getNewNode(int key) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->key = key;
	p->color = 0;
	p->lchild = p->rchild = NIL;
	return p;
}

// 胡医生说：指标合格
void clear(Node *root) {
	if (root == NIL) return ;
	clear(root->lchild);
	clear(root->rchild);
	free(root);
	return;
}

// 胡医生说：指标合格
int has_red_child(Node *root) {
	return root->lchild->color == 0 || root->rchild->color == 0;
}

// 胡医生说：指标合格
Node *left_rotate(Node *root) {
	Node *temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	return temp;
}

// 胡医生说：指标合格
Node *right_rotate(Node *root) {
	Node *temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	return temp;
}

// 胡医生说：指标合格
Node *insert_maintain(Node *root) {
	if (!has_red_child(root)) return root;
	int flag = 0;
	if (root->lchild->color == 0 && has_red_child(root->lchild)) flag = 1;
	if (root->rchild->color == 0 && has_red_child(root->rchild)) flag = 2;
	if (flag == 0) return root;
	// 偷懒没有进行冲突判断
	if (root->lchild->color == 0 && root->rchild->color == 0) {
		root->color = 0;
		root->lchild->color = root->rchild->color = 1;
		return root;
	}
	if (flag == 1) {
		if (root->lchild->rchild->color == 0) {
			root->lchild = left_rotate(root->lchild);
		}
		root = right_rotate(root);
	} else {
		if (root->rchild->lchild->color == 0) {
			root->rchild = right_rotate(root->rchild);
		}
		root = left_rotate(root);
	}
	root->color = 0;
	root->lchild->color = root->rchild->color = 1;
	return root;
}

// 胡医生说：指标合格
Node *__insert(Node *root, int key) {
	if (root == NIL) return getNewNode(key);
	if (root->key == key) return root;
	if (key < root->key) {
		root->lchild = __insert(root->lchild, key);
	}
	else {
		root->rchild = __insert(root->rchild, key);
	}
	return insert_maintain(root);
}

// 胡医生说：指标合格
Node *insert(Node *root, int key) {
	root = __insert(root, key);
	root->color = 1;
	return root;
}

// 胡医生说：指标合格
Node *predecessor(Node *root) {
	Node *temp = root->lchild;
	while (temp->rchild != NIL) temp = temp->rchild;
	return temp;
}

Node *erase_maintain(Node *root) {
	if (root->lchild->color != 2 && root->rchild->color != 2) return root;
	// 兄弟结点是红色
	if (has_red_child(root)) {
		int flag = 0;
		root->color = 0;
		if (root->lchild->color == 0) {
			root = right_rotate(root);
			flag = 1;
		}
		else {
			root = left_rotate(root);
			flag = 2;
		}
		root->color = 1;
		if (flag == 1) root->rchild = erase_maintain(root->rchild);
		else root->lchild = erase_maintain(root->lchild);
		return root;
	}
	// 情况一
	if ((root->lchild->color == 2 && !has_red_child(root->rchild)) ||
		(root->rchild->color == 2 && !has_red_child(root->lchild))) {
		root->lchild->color -= 1;
		root->rchild->color -= 1;
		root->color += 1;
		return root;
	}
	if (root->lchild->color == 2) {
		// RR情况
		if (root->rchild->rchild->color != 0) {
			root->rchild->color = 0;
			root->rchild = right_rotate(root->rchild);
			root->rchild->color = 1;
		}
		root = left_rotate(root);
		root->color = root->lchild->color;
	}
	else {
		// LL情况
		if (root->lchild->lchild->color != 0) {
			root->lchild->color = 0;
			root->lchild = left_rotate(root->lchild);
			root->lchild->color = 1;
		}
		root = right_rotate(root);
		root->color = root->rchild->color;
	}
	root->lchild->color = root->rchild->color = 1;
	return root;
}

// 胡医生说：指标合格
Node *__erase(Node *root, int key) {
	if (root == NIL) return NIL;
	if (key < root->key) {
		root->lchild = __erase(root->lchild, key);
	}
	else if(key > root->key) {
		root->rchild = __erase(root->rchild, key);
	} else {
		if (root->lchild == NIL || root->rchild == NIL) {
			Node *temp = root->lchild != NIL ? root->lchild : root->rchild;
			temp->color += root->color;
			free(root);
			return temp;
		} else {
			Node *temp = predecessor(root);
			root->key = temp->key;
			root->lchild = __erase(root->lchild, temp->key);
		}
	}
	return erase_maintain(root);
}

// 胡医生说：指标合格
Node *erase(Node *root, int key) {
	root = __erase(root, key);
	root->color = 1;
	return root;
}

// 胡医生说：指标合格
void print(Node *root) {
	printf("%d %d %d %d\n", root->key, root->color,
		root->lchild->key, root->rchild->key);
	return;
}

// 胡医生说：指标合格
void output(Node *root) {
	if (root == NIL) return;
	output(root->lchild);
	print(root);
	output(root->rchild);
	return;
}

// 胡医生说：需要住院观察
int main() {
	init_NIL();
    int x, y;
	Node *root = NIL;
	while (scanf("%d%d", &x, &y) != EOF) {
		switch (x) {
            case 1: root = insert(root, y); break;
            case 2: root = erase(root, y); break;
            case 3: output(root); break;
		}
	}
	clear(root);
	return 0;
}
