//
// Created by Xin Sun on 2021-01-18.
//

#include <iostream>
#include <stack>
using namespace std;

class NewDataStruct {
public:
    NewDataStruct(){
        sum[0] = 0;
        ans[0] = INT64_MIN;
    }
    void insert(long long x){
        s1.push(x);
        sum[s1.size()] = sum[s1.size() - 1] + x;
        ans[s1.size()] = max(ans[s1.size() - 1], sum[s1.size()]);
        return;
    }
    void move_left(){
        if(s1.empty()) return;
        long long val = s1.top();
        s2.push(val);
        del();
        return;
    }
    void del(){
        if(s1.empty()) return;
        s1.pop();
        return;
    }

    void move_right(){
        if(s2.empty()) return;
        insert(s2.top());
        s2.pop();
        return;
    }
    long long query(long long i){
        return ans[i];
    }
private:
    stack<long long> s1, s2;
    long long sum[1005];
    long long ans[1005];

};

int main() {
    long long n;
    cin >> n;
    string op;
    int val;
    NewDataStruct s;
    for (int i = 0; i < n; i++) {
        cin >> op;
        switch (op[0]) {
            case 'I': cin >> val; s.insert(val); break;
            case 'D': s.del(); break;
            case 'L': s.move_left(); break;
            case 'R': s.move_right(); break;
            case 'Q': {
                cin >> val;
                cout << s.query(val) << endl;
            } break;
        }
    }
    return 0;
}