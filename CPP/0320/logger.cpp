//
// Created by Xin Sun on 2021-03-30.
//
#include <iostream>
#include <sstream>
#include <mutex>
#include "thread_pool.h"

using namespace std;
#define LOG() Logger::LoggerStream(__FILE__, __LINE__, haizei_log)
#define LOG_INFO LOG()
class Logger {
public:
    class LoggerStream : public ostringstream {
        public:
            LoggerStream(const char* file_name, int line_no, Logger &raw_log) : line_no(line_no), file_name(file_name), raw_log(raw_log){
                ostringstream &now = *this;
                now << "[" << file_name << ": " << line_no  << "]";
            }

            ~LoggerStream() {
                unique_lock<mutex> lock(raw_log.m_mutex);
                cout << str() << endl;
            }
        private:
            int line_no;
            const char *file_name;
            Logger &raw_log;
    };
private:
    std::mutex m_mutex;
};
Logger haizei_log;
void func(int a, int b, int c) {
    LOG_INFO << a << " " << b << " " << c;
    return ;
}
int main()
{
    haizei::ThreadPool tp;
    for (int i = 0; i < 100; i++) {
        tp.addOneTask(func, i, 2 * i, 3 * i);
    }
    tp.stop();
    return 0;
}