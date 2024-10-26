//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOLUSELIB_THREADPOOLMANAGER_H
#define LKTHREADPOOLUSELIB_THREADPOOLMANAGER_H

#include "IThreadPoolManager.h"
#include "IThreadPoolInfo.h"
#include "IThreadPoolControl.h"
#include "ITaskQueueInfo.h"
#include "functional"
#include "thread"
#include "memory"
// #include "TaskQueue.h"
// #include "iostream"

class TaskQueue; // 添加前向声明

//class ThreadPool;

class Timer{
public:
    Timer(long long milliseconds, std::function<void(void)> callback): m_run_flag(false)
            , m_exit_flag(false)
            , m_milliseconds(milliseconds)
            , m_callback(std::move(callback)){
        std::thread([&](){
            while(true){
                while(!m_run_flag){
                    std::this_thread::sleep_for(std::chrono::milliseconds(m_milliseconds));
                }
                if(m_exit_flag){
                    break;
                }
                m_callback();
                std::this_thread::sleep_for(std::chrono::milliseconds(m_milliseconds));
            }
        }).detach();
    };
    ~Timer(){
        exit();
    }
    void start(){
        m_run_flag = true;
    }
    void exit(){
        m_exit_flag = true;
    }
private:
    bool m_run_flag;
    bool m_exit_flag;
    long long m_milliseconds;
    std::function<void(void)> m_callback;
};

class ThreadPoolManager: public IThreadPoolManager{
public:
    ThreadPoolManager(IThreadPoolInfo* ptr, const ITaskQueueInfo* ptr2);
    ~ThreadPoolManager() override = default;
    void start() override;
private:
    IThreadPoolInfo* m_p_thread_pool_info;
    IThreadPoolControl* m_p_thread_pool_control;
    const ITaskQueueInfo* m_p_tasks_queue_info;
    std::shared_ptr<Timer> m_timer;
};


#endif //LKTHREADPOOLUSELIB_THREADPOOLMANAGER_H
