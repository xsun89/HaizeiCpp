//
// Created by Xin Sun on 2021-03-02.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BigInt : public vector<int>{
public:
    BigInt(int);
    void Print();
    void operator+=(int);
    void operator*=(int);
    void operator/=(int);
    BigInt operator/(int);
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
private:
    void processDigit();
};

ostream& operator<< (ostream& stream, const BigInt& data){
    for(int i =data.size() - 1; i >= 0; i--){
        stream << data.at(i);
    }

    return stream;
}
BigInt::BigInt(int x){
    push_back(x);
    processDigit();
}

void BigInt::processDigit()
{
    for(int i = 0; i < size(); i++){
        if(at(i) < 10){
            continue;
        }
        if(i == size() -1){
            push_back(0);
        }
        at(i + 1) += at(i) / 10;
        at(i) %= 10;
    }

    while(size() > 1 && at(size() - 1) == 0) {
        pop_back();
    }
}

void BigInt::operator*=(int x) {
    for(int i = 0; i < size(); i++){
        at(i) *= x;
    }
    processDigit();

    return;
}

void BigInt::operator/=(int x)
{
    int y = 0;
    for(int i = size() - 1; i >= 0; i--){
        y = y * 10 + at(i);
        at(i) = y / x;
        y %= x;
    }

    processDigit();

    return;
}

bool BigInt::operator<(const BigInt &x) const {
    if(size() - x.size()) return size() < x.size();
    for(int i = size() - 1; i >= 0; i--){
        if(at(i) - x.at(i)) return at(i) < x.at(i);
    }

    return false;
}

bool BigInt::operator>(const BigInt &x) const {
    BigInt ret(*this);
    return ret < x;

}
BigInt BigInt::operator/(int x)
{
    BigInt ret(*this);
    ret /= x;
    return ret;
}
void BigInt::operator+=(int x){
    at(0) += x;
    processDigit();
    return;
}
void BigInt::Print()
{
    for(int i = size() - 1; i >= 0; i--){
        cout << at(i);
    }
    cout << endl;

    return;
}
int main()
{
    vector<pair<int, int>> data;
    int n;
    cin >> n;

    for (int i = 0, a, b; i <= n; i++){
        cin >> a >> b;
        data.push_back(make_pair(a, b));
    }

    sort(data.begin() + 1, data.end(),
         [](const pair<int, int> &x, const pair<int, int> &y){
        return x.first * x.second - y.first < y.first * y.second;
    });

    BigInt ans = 0;
    BigInt p = data[0].first;
    for(int i = 1; i <= n; i++){
        ans = max(ans, p / data[i].second);
        p *= data[i].first;
    }

    cout << ans << endl;

    return 0;
}
