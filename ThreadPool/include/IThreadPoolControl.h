//
// Created by banser on 24-10-26.
//

#ifndef LKTHREADPOOLUSELIB_ITHREADPOOLCONTROL_H
#define LKTHREADPOOLUSELIB_ITHREADPOOLCONTROL_H

class IThreadPoolControl{
public:
    IThreadPoolControl() = default;
    virtual ~IThreadPoolControl() = default;
    virtual void set_to_kill_count(int count) = 0;
};

#endif //LKTHREADPOOLUSELIB_ITHREADPOOLCONTROL_H
