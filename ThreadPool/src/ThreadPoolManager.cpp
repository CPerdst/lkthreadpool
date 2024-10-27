//
// Created by banser on 24-10-26.
//

#include "ThreadPoolManager.h"
#include "TaskQueue.h"
#include <iostream>

ThreadPoolManager::ThreadPoolManager(IThreadPoolInfo* ptr, ITaskQueueInfo* ptr2)
    : m_p_thread_pool_info(ptr),
      m_p_thread_pool_control(dynamic_cast<IThreadPoolControl*>(ptr)),
      m_p_tasks_queue_info(ptr2),
      m_p_tasks_queue_control(dynamic_cast<ITaskQueueControl*>(ptr2)),
      m_timer(new Timer(1000, [&]() {
          // check every 10 milliseconds
          auto task_count = m_p_tasks_queue_info->task_count();
          auto max_task_count = m_p_tasks_queue_info->max_task_count();
          auto free_thread_count = m_p_thread_pool_info->get_free_thread_count();
          auto max_thread_count = m_p_thread_pool_info->get_max_thread_count();
          auto min_thread_count = m_p_thread_pool_info->get_min_thread_count();
          auto cur_thread_count = m_p_thread_pool_info->get_cur_thread_count();
          if (static_cast<double>(free_thread_count) / cur_thread_count > 0.7) {
              if (static_cast<double>(task_count) / max_task_count > 0.8) {
                  if (cur_thread_count < max_thread_count)
                    m_p_thread_pool_control->create_thread(1);
              }
          }else if (static_cast<double>(free_thread_count) / cur_thread_count < 0.3) {
              if (static_cast<double>(task_count) / max_task_count < 0.3) {
                  if (cur_thread_count > min_thread_count) {
                      m_p_thread_pool_control->set_to_kill_count(1);
                      m_p_tasks_queue_control->not_empty_notify_one();
                  }
              }
          }
          
      })) {}

void ThreadPoolManager::start(){
    m_timer->start();
}