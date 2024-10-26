//
// Created by banser on 24-10-26.
//

#include "../include/ThreadPool.h"
#include "iostream"

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