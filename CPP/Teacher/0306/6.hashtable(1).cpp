/*************************************************************************
	> File Name: 6.hashtable.cpp
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
using namespace std;

class Node {
public :
    Node() = default;
    Node(string, int, Node *);
    string key();
    int value;
    Node *next();
    void insert(Node *);
    void erase_next();

private:
    string __key;
    Node *__next;
};

class HashTable {
public :
    typedef function<int(string)> HASH_FUNC_T;
    HashTable(HASH_FUNC_T hash_func, int size);
    bool insert(string, int);
    bool erase(string);
    bool find(string);
    int &operator[](string);

private:
    Node *__insert(string, int);
    Node *__find(string);
    int size;
    vector<Node> data;
    HASH_FUNC_T hash_func;
};

Node::Node(string key, int value = 0, Node *next = nullptr) 
: __key(key), value(value), __next(next) {}
string Node::key() { return this->__key; }
Node *Node::next() { return this->__next; }
void Node::insert(Node *p) { 
    p->__next = this->__next; 
    this->__next = p;
    return ;
}
void Node::erase_next() { 
    if (this->__next == nullptr) return ;
    Node *q = this->__next; 
    this->__next = this->__next->__next;
    delete q;
    return ;
}

HashTable::HashTable(HASH_FUNC_T hash_func, int size = 10000) 
: size(size), data(size), hash_func(hash_func) {}

bool HashTable::insert(string key, int value = 0) {
    if (find(key)) return false;
    return __insert(key, value);
}
Node *HashTable::__insert(string key, int value = 0) {
    int h = hash_func(key) % size;
    data[h].insert(new Node(key, value));
    return data[h].next();
}

bool HashTable::erase(string s) {
    int h = hash_func(s) % size;
    for (Node *p = &data[h]; p->next(); p = p->next()) {
        if (p->next()->key() != s) continue;
        p->erase_next();
        return true;
    }
    return false;
}

bool HashTable::find(string s) {
    return __find(s);
}
Node *HashTable::__find(string key) {
    int h = hash_func(key) % size;
    for (Node *p = data[h].next(); p; p = p->next()) {
        if (p->key() == key) return p;
    }
    return nullptr;
}

int &HashTable::operator[](string key) {
    Node *p;
    if (!(p = __find(key))) return (__insert(key)->value);
    return p->value;
}

int BKDRHash(string s) {
    int seed = 31;
    int h = 0;
    for (int i = 0; s[i]; i++) {
        h = h * seed + s[i];
    }
    return h & 0x7fffffff;
}

class APHash_Class {
public :
    int operator()(string s) {
        int h = 0;
        for (int i = 0; s[i]; i++) {
            if (i % 2) {
                h = (h << 3) ^ s[i] ^ (h >> 5);
            } else {
                h = ~((h << 7) ^ s[i] ^ (h >> 11));
            }
        }
        return h & 0x7fffffff;
    }
};

int main() {
    APHash_Class APHash;
    HashTable h1(BKDRHash);
    HashTable h2(APHash);
    int op;
    string s;
    h1["hello"] = 123;
    h1["world"] = 456;
    cout << h1["hello"] << " " << h1["world"] << " " << h1["hahaha"] << endl;
    while (cin >> op >> s) {
        switch (op) {
            case 0: {
                cout << "insert " << s << " to hash table 1 = ";
                cout << h1.insert(s) << endl;
                cout << "insert " << s << " to hash table 2 = ";
                cout << h2.insert(s) << endl;
            } break; // insert
            case 1: {
                cout << "erase " << s << " from hash table 1 = ";
                cout << h1.erase(s) << endl;
                cout << "erase " << s << " from hash table 2 = ";
                cout << h2.erase(s) << endl;
            } break; // erase
            case 2: {
                cout << "find " << s << " at hash table 1 = ";
                cout << h1.find(s) << endl;
                cout << "find " << s << " at hash table 2 = ";
                cout << h2.find(s) << endl;
            } break; // find
        }
    }
    return 0; 
}
