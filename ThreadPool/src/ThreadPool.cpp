//
// Created by banser on 24-10-26.
//

#include "iostream"
#include "ThreadPool.h"
#include "ThreadPoolManager.h"

ThreadPool::ThreadPool(int min_t, int max_t, int max_task_count)
    : m_min_t(min_t),
      m_max_t(max_t),
      m_max_task_count(max_task_count),
      m_busy_thread_count(0),
      m_threads_vec(),
      m_run_flag(false),
      m_stop_flag(false),
      m_task_queue(std::make_shared<TaskQueue>(max_task_count)),
      m_to_kill_count(0),
      m_thread_pool_manager(std::make_shared<ThreadPoolManager>(this, dynamic_cast<TaskQueue*>(m_task_queue.get()))) {}

void ThreadPool::start(){
    if(!m_threads_vec.empty()){
        m_stop_flag = true;
        return;
    }
    m_run_flag = true;
    for(int i = 0; i < m_min_t; i++){
        auto t = std::thread([&](){
            while(m_run_flag){
                while(m_stop_flag){
                    std::this_thread::sleep_for(std::chrono::microseconds(1000));
                }
                auto task = m_task_queue->get_task();
                {
                    std::unique_lock<std::mutex> lock(m_var_mtx);
                    m_busy_thread_count++;
                }
                task();
                {
                    std::unique_lock<std::mutex> lock(m_var_mtx);
                    m_busy_thread_count--;
                }
            }
            {
                std::unique_lock<std::mutex> lock(m_var_mtx);
                std::cout << std::this_thread::get_id() << " thread exit." << std::endl;
            }
        });
        t.detach();
        m_threads_vec.push_back(std::move(t));
    }
    m_thread_pool_manager->start();
}

void ThreadPool::stop(){
    m_stop_flag = true;
}

void ThreadPool::exit(){
    m_run_flag = false;
}

void ThreadPool::add_task(std::function<void ()> task){
    m_task_queue->add_task(task);
}

int ThreadPool::get_max_thread_count(){
    std::unique_lock<std::mutex> lock(m_var_mtx);
    return m_max_task_count;
}

int ThreadPool::get_free_thread_count(){
    std::unique_lock<std::mutex> lock(m_var_mtx);
    return m_threads_vec.size() - m_busy_thread_count;
}

void ThreadPool::set_to_kill_count(int count) {
    std::unique_lock<std::mutex> out_lock(m_to_kill_count_mtx);
    {
        std::unique_lock<std::mutex> in_lock(m_var_mtx);
        if(m_threads_vec.size() - count < m_min_t){
            count = m_threads_vec.size() - m_min_t;
        }
    }
    m_to_kill_count = count;
}

int ThreadPool::get_to_kill_count() {
    std::unique_lock<std::mutex> lock(m_to_kill_count_mtx);
    return m_to_kill_count;
}
