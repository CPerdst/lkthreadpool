//
// Created by banser on 24-10-26.
//

#include "ThreadPoolManager.h"
#include "TaskQueue.h"
#include <iostream>

ThreadPoolManager::ThreadPoolManager(IThreadPoolInfo* ptr, const ITaskQueueInfo* ptr2)
    : m_p_thread_pool_info(ptr),
      m_p_thread_pool_control(dynamic_cast<IThreadPoolControl*>(ptr)),
      m_p_tasks_queue_info(ptr2),
      m_timer(new Timer(10, []() {
          // check every 10 milliseconds
          std::cout << "Timer CallBack" << std::endl;
      })) {}

void ThreadPoolManager::start(){
    m_timer->start();
}