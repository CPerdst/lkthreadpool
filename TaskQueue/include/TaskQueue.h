//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOL_TASKQUEUE_H
#define LKTHREADPOOL_TASKQUEUE_H

#include "ITaskQueue.h"
#include "ITaskQueueInfo.h"
#include "mutex"
#include "condition_variable"
#include "queue"

class TaskQueue: public ITaskQueue, public ITaskQueueInfo{
public:
    TaskQueue(int max_task_count = 10000): m_max_task_count(max_task_count) {};
    ~TaskQueue() = default;
    void add_task(std::function<void(void)> task) override;
    std::function<void(void)> get_task() override;
    int task_count() override;
private:
    int m_max_task_count;
    std::mutex m_mtx;
    std::condition_variable m_cond_not_empty;
    std::condition_variable m_cond_not_full;
    std::queue<std::function<void(void)>> m_tasks_que;
};


#endif //LKTHREADPOOL_TASKQUEUE_H
