//
// Created by Xin Sun on 2021-03-03.
//
#include <string>
#include <iostream>

using namespace std;

int main()
{
    int n;
    string a, b;
    cin >> a >> n >> b;

    int len = a.length();
    if(len > 100){
        cout << 100 << endl;
    }else{
        cout << len << endl;
    }

    a.insert(n - 1, b);
    cout << a << endl;
    int pos = a.find_last_of('x');
    cout << pos << endl;
    cout << a.length() - pos  << endl;

    return 0;
}
