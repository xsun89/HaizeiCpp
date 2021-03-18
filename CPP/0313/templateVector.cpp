//
// Created by Xin Sun on 2021-03-15.
//
#include <iostream>
#include <vector>

using namespace std;

class A{
public:
    A() = delete;
    A(int x) : x(x){}
    friend ostream &operator<<(ostream &, const A &);
private:
    int x;
};

ostream &operator<<(ostream &out, const A &a){
    out << a.x;

    return out;
}

namespace haizei
{
    template <typename T>
    class vector{
        public:
            vector(int n = 10);
            vector(const vector&v);
            vector(vector<T> &v);
            T& operator[](int);
            const T& operator[](int) const;
            int size() const;
            int capacity() const;
            void push_back(const T &);
            void push_back(T &&);

            ~vector();
        private:
            int __size;
            int __capacity;
            T *data;
    };
    template<typename T>
    vector<T>::vector(int n) : __size(0), __capacity(n), data(nullptr)
    {
        data = (T *)malloc(sizeof(T) * __capacity);
        return;
    }

    template<typename T>
    vector<T>::vector(const vector&v) : __size(v.__size), __capacity(v.__capacity), data(nullptr)
    {
        data = (T *)malloc(sizeof(T) * __capacity);
        for(int i = 0; i < v.capacity(); i++){
            new (data + 1) T(v.data[i]);
        }

        return;
    }

    template <typename T>
    vector<T>::vector(vector<T> &v) : __size(v.__size), __capacity(v.capacity()), data(v.data)
    {
        v.data = nullptr;
        v.__capacity = 0;
        v.__size = 0;
    }

    template<typename T>
    T& vector<T>::operator[](int ind){
        return data[ind];
    }

    template<typename T>
    const T& vector<T>::operator[](int ind) const
    {
        return data[ind];
    }

    template<typename T>
    int vector<T>::size() const
    {
        return __size;
    }

    template<typename T>
    int vector<T>::capacity() const
    {
        return __capacity;
    }

    template<typename T>
    vector<T>::~vector()
    {
        if(data) free(data);
        __capacity = 0;
        __size = 0;
        return ;
    }

    template <typename T>
    void vector<T>::push_back(const T &val)
    {
        if(__size < __capacity)
            new (data + __size) T(val);
        __size += 1;
        return;
    }

    template <typename T>
    void  vector<T>::push_back(T &&val){
        new (data + __size) T(move(val));
        __size += 1;
    }
}

ostream &operator<<(ostream &out, const vector<A> &a)
{
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    return out;
}

ostream &operator<<(ostream &out, const haizei::vector<A> &a)
{
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    return out;
}

int main()
{
    vector<A> v1;
    cout << v1.size() << endl;
    v1.push_back(123);
    v1.push_back(456);
    v1.push_back(789);
    haizei::vector<A> v2;
    cout << v2.size() << endl;
    v2.push_back(123);
    v2.push_back(456);
    v2.push_back(789);
    cout << v1 << endl;
    cout << v2 << endl;
}