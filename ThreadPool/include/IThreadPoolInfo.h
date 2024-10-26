//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOL_ITHREADPOOLINFO_H
#define LKTHREADPOOL_ITHREADPOOLINFO_H

class IThreadPoolInfo{
public:
    IThreadPoolInfo() = default;
    virtual ~IThreadPoolInfo() = default;
    virtual int get_max_thread_count() = 0;
    virtual int get_free_thread_count() = 0;
};

#endif //LKTHREADPOOL_ITHREADPOOLINFO_H
