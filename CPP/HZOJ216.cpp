//
// Created by Xin Sun on 2021-03-03.
//

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    int n;
    cin >> n;
    map<string, int> m;
    string a;
    for (int i = 0; i < n; i++){
        cin >> a;
        a = a.substr(3);
        m[a] += 1;
    }

    for (auto it = m.begin() ; it != m.end() ; it++){
        for(int i = 1; i <= it->second; i++){
            cout << it->first << endl;
        }
    }
    return 0;
}