//
// Created by banser on 24-10-26.
//

#include "TaskQueue.h"

#include "IThreadPoolControl.h"

void TaskQueue::add_task(std::function<void(void)> task){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(m_tasks_que.size() >= m_max_task_count){
        m_cond_not_full.wait(lock, [&](){return m_tasks_que.size() < m_max_task_count;});
    }
    m_tasks_que.push(std::move(task));
    m_cond_not_empty.notify_one();
}

std::function<void(void)> TaskQueue::get_task(IThreadPoolInfo* pThis, int& err){
    std::unique_lock<std::mutex> lock(m_mtx);
    if(m_tasks_que.empty()) {
        m_cond_not_empty.wait(lock, [&]() { return pThis->get_to_kill_count() || !m_tasks_que.empty(); });
        if (pThis->get_to_kill_count()) {
            const int count = pThis->get_to_kill_count();
            dynamic_cast<IThreadPoolControl*>(pThis)->set_to_kill_count(count - 1);
            err = 1;
            auto task = [](){return;};
            return task;
        }
    }
    auto task = std::move(m_tasks_que.front());
    m_tasks_que.pop();
    m_cond_not_full.notify_one();
    err = 0;
    return task;
}

int TaskQueue::task_count() const{
    return static_cast<int>(m_tasks_que.size());
}

int TaskQueue::max_task_count() const{
    return m_max_task_count;
}

void TaskQueue::not_empty_notify_one() {
    m_cond_not_empty.notify_one();
}

void TaskQueue::not_full_notify_one() {
    m_cond_not_full.notify_one();
}