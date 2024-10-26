//
// Created by banser on 24-10-26.
//

#include "TaskQueue.h"

void TaskQueue::add_task(std::function<void(void)> task){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(m_tasks_que.size() >= m_max_task_count){
        m_cond_not_full.wait(lock, [&](){return m_tasks_que.size() < m_max_task_count;});
    }
    m_tasks_que.push(std::move(task));
    m_cond_not_empty.notify_one();
}

std::function<void(void)> TaskQueue::get_task(){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(m_tasks_que.empty()) {
        m_cond_not_empty.wait(lock, [&]() { return !m_tasks_que.empty(); });
    }
    auto task = std::move(m_tasks_que.front());
    m_tasks_que.pop();
    m_cond_not_full.notify_one();
    return task;
}

int TaskQueue::task_count(){
    std::unique_lock<std::mutex> lock(m_mtx);
    return m_tasks_que.size();
}