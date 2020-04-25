#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <iostream>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace haizei {
    class Task {
    public :
        template<typename Func_T, typename ...ARGS>
        Task(Func_T f, ARGS ...args) {
            func = std::bind(f, std::forward<ARGS>(args)...);
        }
        
        void run() {
            func();
        }

    private:
        std::function<void()> func;
    };

    class thread_pool {
    public:        
        thread_pool(int thread_size = 5) : thread_size(thread_size), is_started(false), m_mutex(), m_cond(), m_queue_cond(), m_queue_mutex(), m_mutex2() {}
        
        void start() {
            std::unique_lock<std::mutex> lock(m_mutex);
            is_started = true;
            for (int i = 0; i < thread_size; i++) {
                Threads.push_back(new std::thread(&thread_pool::thread_loop, this));
            }
        }
        
        void stop() {
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                is_started = false;
                m_cond.notify_all();
            }
            for (int i = 0; i < Threads.size(); i++) {
                Threads[i]->join();
                delete Threads[i];
            }
            Threads.clear();
            return ;
        }
        
        template<typename Func_T, typename ...ARGS>
        void add_one_task(Func_T f, ARGS...args) {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            __add_one_task(new Task(f, std::forward<ARGS>(args)...));
        }
        
        void stop_until_empty() {
            std::unique_lock<std::mutex> lock1(m_mutex2);
            std::unique_lock<std::mutex> lock2(m_queue_mutex);
            while (!Tasks.empty()) {
                m_queue_cond.wait(lock1);
            }
            stop();
            return ;
        }
        
        ~thread_pool() { stop(); }

    private:
        int thread_size;
        volatile bool is_started;
        std::vector<std::thread *> Threads;
        std::queue<Task *> Tasks;
        std::mutex m_mutex, m_mutex2, m_queue_mutex;
        std::condition_variable m_cond, m_queue_cond;
        
        void thread_loop() {
            while (is_started) {
                Task *t = get_one_task();
                if (t != nullptr) t->run();
            }
            return ;
        }
        
        Task *get_one_task() {
            std::unique_lock<std::mutex> lock(m_mutex);
            while (Tasks.empty() && is_started) {
                m_cond.wait(lock);
            }
            Task *t = nullptr;
            if (!Tasks.empty() && is_started) {
                t = Tasks.front();
                Tasks.pop();
                if (Tasks.empty()) {
                    std::unique_lock<std::mutex> lock2(m_mutex2);
                    m_queue_cond.notify_all();
                }
            }
            return t;
        }
        
        void __add_one_task(Task *t) {
            std::unique_lock<std::mutex> lock(m_mutex);
            Tasks.push(t);
            m_cond.notify_one();
            return ;
        }
    };
}

#endif
