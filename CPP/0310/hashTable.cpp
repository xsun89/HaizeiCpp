//
// Created by Xin Sun on 2021-03-11.
//
// Hash node class template
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node {
public:
    Node() = default;
    Node(string key, Node *next = nullptr) :
        _key(key), _next(next) {
    }
    string getKey() const {
        return _key;
    }
    Node *getNext() const {
        return _next;
    }
    void insert(Node *p){
       p->_next = this->_next;
       this->_next = p;
       return ;
    }

    void erase_next(){
        if(this->_next == nullptr) return;
        Node *p = this->_next;
        this->_next = this->_next->_next;
        delete p;
        return;
    }
private:
    string _key;
    // next bucket with the same key
    Node *_next;
};

class HashTable {
public :
    typedef function<int(string)> HASH_FUNC_T;
    HashTable(HASH_FUNC_T hash_func, int size);
    bool insert(string);
    bool erase(string);
    bool find(string);

private:
    int size;
    vector<Node> data;
    HASH_FUNC_T hash_func;
};

HashTable::HashTable(HASH_FUNC_T hash_func, int size = 1000)
    :hash_func(hash_func), data(size), size(size){
}

bool HashTable::insert(string key)
{
    if(find(key)) return false;
    int h = this->hash_func(key) % size;
    data[h].insert(new Node(key));
    return true;
}
bool HashTable::erase(string s)
{
    if(!find(s)) return false;
    int h = hash_func(s) % size;
    for(Node *p = data[h].getNext(); p != nullptr; p = p->getNext())
    {
        if(p->getKey() == s){
            p->erase_next();
            return true;
        }
    }
    return false;
}
bool HashTable::find(string s)
{
    int h = hash_func(s) % size;
    for(Node *n = data[h].getNext(); n; n = n->getNext()){
        if(s == n->getKey()){
            return true;
        }
    }
    return false;
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

