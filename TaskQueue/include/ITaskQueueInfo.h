//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOL_ITASKQUEUEINFO_H
#define LKTHREADPOOL_ITASKQUEUEINFO_H

class ITaskQueueInfo{
public:
    ITaskQueueInfo() = default;
    ~ITaskQueueInfo() = default;
    virtual int task_count() = 0;
};

#endif //LKTHREADPOOL_ITASKQUEUEINFO_H
