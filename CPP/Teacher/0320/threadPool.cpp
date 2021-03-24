/*************************************************************************
	> File Name: threadPool.cpp
	> Author: LXF
	> Mail: 
	> Created Time: Sun Mar 21 18:13:11 2021
 ************************************************************************/

#include<iostream>
#include<queue>
#include<thread>
#include<functional>
using namespace std;



class ThreadPool{
public:
    ThreadPool(){
        //创建线程
    }
    void run(){//运行任务
        //锁
        //取出一个任务运行
        //解锁
    }
    void add(thread t){//增加任务
        
    }
private:
    queue<thread> Q;
};

void func(){
}

int main(){
//    thread t(func);
    queue<int> q;
    q.push(1);
    q.front();
    q.pop();
    return 0;
}
