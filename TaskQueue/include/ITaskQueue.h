//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOL_ITASKQUEUE_H
#define LKTHREADPOOL_ITASKQUEUE_H

#include "functional"
#include "IThreadPoolInfo.h"

class ITaskQueue{
public:
    ITaskQueue() = default;

    virtual ~ITaskQueue() = default;
    virtual void add_task(std::function<void(void)> task) = 0;
    virtual std::function<void(void)> get_task(IThreadPoolInfo* pThis, int& err) = 0;
};

#endif //LKTHREADPOOL_ITASKQUEUE_H
