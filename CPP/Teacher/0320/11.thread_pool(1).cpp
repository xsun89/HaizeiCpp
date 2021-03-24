/*************************************************************************
	> File Name: 11.thread_pool.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <vector>
#include <thread>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace haizei {

class Task {
public :
    template<typename FUNCTION, typename ...ARGS>
    Task(FUNCTION &&func, ARGS ...args);
    void run();

private:
    std::function<void()> func;
};

class ThreadPool {
public :
    ThreadPool(int n = 5);
    template<typename FUNCTION, typename ...ARGS>
    void addOneTask(FUNCTION &&, ARGS...);
    void stop();

private:
    std::vector<std::thread *> threads;
    std::queue<Task *> tasks;
    std::unordered_map<std::thread::id, bool> running;
    std::mutex m_mutex;
    std::condition_variable m_cond;

    void worker_thread();
    Task *getOneTask();
};

template<typename FUNCTION, typename ...ARGS>
Task::Task(FUNCTION &&func, ARGS ...args) {
    this->func = std::bind(func, std::forward<ARGS>(args)...);
}

void Task::run() {
    std::cout << "Task run : " << std::endl;
    func();
    return ;
}

ThreadPool::ThreadPool(int n) {
    for (int i = 0; i < n; i++) {
        threads.push_back(new std::thread(&ThreadPool::worker_thread, this));
    }
    return ;
}

void ThreadPool::worker_thread() {
    std::thread::id id = std::this_thread::get_id();
    running[id] = true;
    while (running[id]) {
        // 取任务
        Task *t = this->getOneTask();
        // 执行任务
        if (t == nullptr) return ;
        t->run();
        // 销毁任务
        delete t;
    }
    return ;
}

template<typename FUNCTION, typename ...ARGS>
void ThreadPool::addOneTask(FUNCTION &&func, ARGS... args) {
    std::unique_lock<std::mutex> lock(m_mutex);
    tasks.push(new Task(func, std::forward<ARGS>(args)...));
    m_cond.notify_one();
    return ;
}

Task *ThreadPool::getOneTask() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (tasks.empty()) {
        m_cond.wait(lock);
    }
    if (running[std::this_thread::get_id()] == false) return nullptr;
    Task *t = tasks.front();
    tasks.pop();
    return t;
}

void ThreadPool::stop() {
    // TODO
    std::unique_lock<std::mutex> ulock(m_mutex);
    for (auto kv : running) {
        kv.second = false;
    }
    ulock.unlock();
    m_cond.notify_all();
    for (Task* t : threads) {
        if (t->joinable()) t->join();
        delete t;
    }
    return ;
}

} // end of haizei

void func(int a, int b, int c) {
    std::cout << "func id : " << a << ", " << a + b + c << std::endl;
    return ;
}

int main() {
    haizei::ThreadPool tp;
    for (int i = 0; i < 100; i++) {
        tp.addOneTask(func, i, 2 * i, 3 * i);
    }
    tp.stop();
    return 0;
}
