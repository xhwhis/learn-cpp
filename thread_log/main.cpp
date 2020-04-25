#include <iostream>
#include "logger.h"
#include "thread_pool.h"
using namespace std;

void func1() {
    cout << "1" << "2" << "3" << "4" << "5" << "6" << endl;
    return ;
}

void func2() {
    LOG_INFO << "info: " "1" << "2" << "3" << "4" << "5" << "6";
    LOG_DEBUG << "debug: " "1" << "2" << "3" << "4" << "5" << "6";
    LOG_WARN << "warn: " "1" << "2" << "3" << "4" << "5" << "6";
    LOG_ERROR << "error: " "1" << "2" << "3" << "4" << "5" << "6";
    return ;
}

int main() {
    haizei::thread_pool tp(10);
    tp.start();
    for (int i = 1; i <= 20; i++) {
        tp.add_one_task(func1);
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    tp.stop();
    cout << "cout done" << endl;
    cout.flush();
    tp.start();
    for (int i = 1; i <= 20; i++) {
        tp.add_one_task(func2);
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    tp.stop();
    cout << "log done" << endl;
    return 0;
}
