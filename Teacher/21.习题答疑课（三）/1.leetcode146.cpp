/*************************************************************************
	> File Name: leetcode.146.cpp
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
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    class Node {
    public :
        Node() : Node(0, 0) {}
        Node(int key, int value) : pre(nullptr), next(nullptr), key(key), value(value) {}
        Node *pre, *next;
        int key, value;
    };
    int capacity, node_cnt;
    unordered_map<int, Node *> ind;
    Node head, tail;
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->node_cnt = 0;
        head.next = &tail;
        tail.pre = &head;
    }
    int get(int key) {
        if (ind.find(key) == ind.end()) return -1;
        Node *p = ind[key];
        remove_node(p);
        insert_tail(p);
        return p->value;
    }
    void output() {
        Node *p = head.next;
        while (p) {
            cout << "(" << p->key << ", " << p->value << ")->";
            p = p->next;
        }
        cout << endl;
        return ;
    }
    void remove_node(Node *p) {
        p->next->pre = p->pre;
        p->pre->next = p->next;
        return ;
    }
    void insert_tail(Node *p) {
        p->next = &tail;
        p->pre = tail.pre;
        tail.pre = p;
        return ;
    }
    void put(int key, int value) {
        Node *p;
        if (ind.find(key) == ind.end()) {
            p = new Node(key, value);
            node_cnt += 1;
            insert_tail(p);
            ind[key] = p;
        } else {
            get(key);
        }
        if (node_cnt > capacity) {
            p = head.next;
            remove_node(p);
            delete p;
            node_cnt -= 1;
        }
        return ;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
