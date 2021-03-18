//
// Created by Xin Sun on 2021-03-14.
//
/*
 * left bind left, right bind right, const left can bind to any
 * no middle valuable ==> left value
 * middle valuable ==>right value
 *
 * x = 3; x is left value
 * 3 + x is right value
 * x++
 */
#include <iostream>

using namespace std;
#define func(x) __func(x, "func(" #x ")")
#define func2(x) __func2(x, "func2(" #x ")")

void __func2(int &x, const char * str){
    //cout << __PRETTY_FUNCTION__ << endl;
    cout << str << " is left value" << endl;
    return;
}

void __func2(int &&x, const char * str){
    //cout << __PRETTY_FUNCTION__ << endl;
    cout << str << " is right value" << endl;
    return;
}
void __func(int &x, const char * str){
    //cout << __PRETTY_FUNCTION__ << endl;
    cout << str << " is left value" << endl;
    func2(x);
    return;
}

void __func(int &&x, const char * str){
    //cout << __PRETTY_FUNCTION__ << endl;
    cout << str << " is right value" << endl;
    func2(move(x));
    return;
}

namespace haizei {
    class vector{
        public:
            vector(int n=10) : __size(n), data(new int[n]) {
                cout << "default constructor" << endl;
            }
            vector(const vector &v) : __size(v.__size), data(new int(v.__size)){
                cout << "copy constructor" << endl;
                for (int i = 0; i < v.__size; i++){
                    data[i] = v[i];
                }
            }
            vector(vector &&v) : __size(v.__size), data(v.data){
                cout << "copy move constructor" << endl;
                v.data = nullptr;
                v.__size = 0;
            }
            vector &operator+(const vector &v1){
                vector *v2 = new haizei::vector(v1.__size + this->__size);
                vector now = (*this);
                for (int i = 0; i < __size; i++){
                    (*v2)[i] = now[i];
                }
                for (int i = __size; i < v2->__size; i++){
                    (*v2)[i] = v1[i - __size];
                }

                return *v2;
            }
            int &operator[](int i) const{
                return this->data[i];
            }

            int size() const {
                return this->__size;
            }
        private:
            int __size;
            int *data;

    };
}

ostream& operator<<(ostream &out, const haizei::vector &v){
    for (int i = 0; i < v.size(); i++) {
        out << v[i] << " ";
    }
    return out;
}
int main()
{
    haizei::vector v1, v2;
    for(int i = 0; i < v1.size(); i++) v1[i] = rand() % 10;
    for(int i = 0; i < v2.size(); i++) v2[i] = rand() % 10;
    //haizei::vector v3(v1 + v2);
    cout << v1 << endl;
    cout << v2 << endl;
    cout << v1 + v2 << endl;
    haizei:: vector v4(move(v1));
    cout << v1 << endl;
    cout << v4 << endl;
    int x = 123, y = 456;
    func(x);
    func(x + y);
    func(x += y);
    func(x++);
    func(++x);
    return 0;
}