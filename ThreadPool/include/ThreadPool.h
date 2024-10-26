//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOL_THREADPOOL_H
#define LKTHREADPOOL_THREADPOOL_H

#include "TaskQueue.h"
#include "IThreadPool.h"
#include "IThreadPoolInfo.h"
#include "ITaskQueue.h"
#include "vector"
#include "thread"
#include "memory"
#include "mutex"
#include "IThreadPoolControl.h"
#include "IThreadPoolManager.h"
#include "ThreadPoolManager.h"

class ThreadPool: public IThreadPool, public IThreadPoolInfo, public IThreadPoolControl{
public:
    ThreadPool(int min_t, int max_t, int max_task_count): m_min_t(min_t)
    , m_max_t(max_t)
    , m_max_task_count(max_task_count)
    , m_busy_thread_count(0)
    , m_threads_vec(0)
    , m_run_flag(false)
    , m_stop_flag(false)
    , m_task_queue(new TaskQueue(max_task_count))
    , m_to_kill_count(0)
    , m_thread_pool_manager(new ThreadPoolManager(this, m_task_queue.get())){};
    ~ThreadPool() override = default;
    void start() override;
    void stop() override;
    void exit() override;
    void add_task(std::function<void ()> task) override;
    int get_max_thread_count() override;
    int get_free_thread_count() override;
    void set_to_kill_count(int count) override;
    int get_to_kill_count();
private:
    int m_min_t;
    int m_max_t;
    int m_max_task_count;
    int m_busy_thread_count;
    std::mutex m_var_mtx;
    std::vector<std::thread> m_threads_vec;
    bool m_run_flag;
    bool m_stop_flag;
    std::shared_ptr<ITaskQueue> m_task_queue;
    int m_to_kill_count;
    std::mutex m_to_kill_count_mtx;
    std::shared_ptr<IThreadPoolManager> m_thread_pool_manager;
};

#endif //LKTHREADPOOL_THREADPOOL_H
