//
// Created by parallels on 24-10-27.
//

#ifndef ITASKQUEUECONTROL_H
#define ITASKQUEUECONTROL_H

class ITaskQueueControl {
public:
    ITaskQueueControl() = default;
    virtual ~ITaskQueueControl() = default;
    virtual void not_empty_notify_one() = 0;
    virtual void not_full_notify_one() = 0;
};

#endif //ITASKQUEUECONTROL_H
