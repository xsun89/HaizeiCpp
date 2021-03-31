//
// Created by Xin Sun on 2021-03-30.
//
#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <condition_variable>

using namespace std;

class Task {
public:
    template<typename FUNCTION, typename ...ARGS>
    Task(FUNCTION &&func, ARGS ...args);
    void run();

private:
    function<void()> func;
};
template<typename FUNCTION, typename ...ARGS>
Task::Task(FUNCTION &&func, ARGS ...args){
    this->func = bind(func, forward<ARGS>(args)...);
}

void Task::run(){
    this->func();
}

class MyThreadPool {
public:
    MyThreadPool(int n = 5);
    template<typename FUNCTION, typename ...ARGS>
    void addOneTask(FUNCTION &&func, ARGS ...args);
    void stop();

private:
    vector<thread *> threads;
    void worker_thread();
    queue<Task *> tasks;
    unordered_map<thread::id, bool> running;
    mutex m_mutex;
    condition_variable m_cnd;
    Task *getOneTask();
    void stop_thread();
};

MyThreadPool::MyThreadPool(int n){
    for(int i = 0; i < n; i++) {
        this->threads.push_back(new thread(&MyThreadPool::worker_thread, this));
    }

    return;
}

void MyThreadPool::worker_thread(){
    std::thread::id id = std::this_thread::get_id();
    running[id] = true;
    while(running[id]){
        Task *t = getOneTask();
        t->run();
        delete t;
    }
}

Task *MyThreadPool::getOneTask(){
    unique_lock<mutex> lock(m_mutex);
    while(tasks.empty()) {
        m_cnd.wait(lock);
    }
    Task *t = tasks.front();
    tasks.pop();
    return t;
}

template<typename FUNCTION, typename ...ARGS>
void MyThreadPool::addOneTask(FUNCTION &&func, ARGS... args){
    unique_lock<mutex> lock(m_mutex);
    tasks.push(new Task(func, forward<ARGS>(args)...));
    m_cnd.notify_one();

    return;
}

void MyThreadPool::stop_thread(){
    std::thread::id id = std::this_thread::get_id();
    running[id] = false;

    return;
}
void MyThreadPool::stop(){
    unique_lock<mutex> lock(m_mutex);
    for(int i = 0; i < threads.size(); i++) {
        this->tasks.push(new Task(&MyThreadPool::stop_thread, this));
    }
    for(auto th : threads){
        th->join();
    }
    return;
}

void func(int a, int b, int c) {
    std::thread::id id = std::this_thread::get_id();
    std::cout << "func id : " << a << ", " << a + b + c << std::endl;
    return ;
}

int main() {
    MyThreadPool tp;
    for (int i = 0; i < 100; i++) {
        tp.addOneTask(func, i, 2 * i, 3 * i);
    }
    tp.stop();
    return 0;
}
