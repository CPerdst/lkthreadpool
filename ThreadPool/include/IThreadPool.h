//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOL_ITHREADPOOL_H
#define LKTHREADPOOL_ITHREADPOOL_H

#include "functional"

class IThreadPool{
public:
    IThreadPool() = default;
    virtual ~IThreadPool() = default;
    virtual void start() = 0;
    [[maybe_unused]] virtual void stop() = 0;
    [[maybe_unused]] virtual void exit() = 0;
    virtual void add_task(std::function<void(void)> task) = 0;
};

#endif //LKTHREADPOOL_ITHREADPOOL_H
