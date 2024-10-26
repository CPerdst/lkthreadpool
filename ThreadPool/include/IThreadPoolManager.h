//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOLUSELIB_ITHREADPOOLMANAGER_H
#define LKTHREADPOOLUSELIB_ITHREADPOOLMANAGER_H


class IThreadPoolManager {
public:
    IThreadPoolManager() = default;
    virtual ~IThreadPoolManager() = default;
    virtual void start() = 0;
};


#endif //LKTHREADPOOLUSELIB_ITHREADPOOLMANAGER_H
