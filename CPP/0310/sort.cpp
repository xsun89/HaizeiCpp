//
// Created by Xin Sun on 2021-03-10.
//
#include <iostream>

using namespace std;
class CMP {
public :
    CMP(int z = 0) : z(z) {} // z = 0 less,  z = 1 greater
    bool operator()(int a, int b) {
        return (a < b) ^ !!(z);
    }
    int z;
};

void sort(int *p, int l, int r, function<bool(int, int)>cmp){
    if(l >= r) return;
    int x = l;
    int y = r;
    int m = (x + y) >> 1;
    do{
        while(cmp(p[m], p[y])) y--;
        while(cmp(p[x], p[m])) x++;
        if(x <= y){
            swap(p[x], p[y]);
            x++, y--;
        }
    }while(x <= y);
    sort(p, l, y, cmp);
    sort(p, x, r, cmp);

    return;
}
int main()
{
    int arr2[5] = {6, 8, 4, 5, 1};
    sort(arr2, 0, 4, CMP(0));
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    sort(arr2, 0, 4, CMP(1));
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}
