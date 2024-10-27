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
#include "ITaskQueueControl.h"
#include "IThreadPoolInfo.h"

class TaskQueue: public ITaskQueue, public ITaskQueueInfo, public ITaskQueueControl{
public:
    explicit TaskQueue(int max_task_count = 10000): m_max_task_count(max_task_count) {};
    ~TaskQueue() override = default;
    void add_task(std::function<void(void)> task) override;
    std::function<void(void)> get_task(IThreadPoolInfo* pThis, int& err) override;
    [[nodiscard]] int task_count() const override;
    [[nodiscard]] int max_task_count() const override;
    void not_empty_notify_one() override;
    void not_full_notify_one() override;
private:
    int m_max_task_count;
    std::mutex m_mtx;
    std::condition_variable m_cond_not_empty;
    std::condition_variable m_cond_not_full;
    std::queue<std::function<void(void)>> m_tasks_que;
};


#endif //LKTHREADPOOL_TASKQUEUE_H
