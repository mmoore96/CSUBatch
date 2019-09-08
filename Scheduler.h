//
// Created by trcoo on 9/3/19.
//

#ifndef CSUBATCH_SCHEDULER_H
#define CSUBATCH_SCHEDULER_H

#include "main.h"
#include "JobQueue.h"
#include "unistd.h"
#define fcfs_enum 0
#define sjf_num 1
#define priority_num 2



void* run_scheduler(void *data);


#endif //CSUBATCH_SCHEDULER_H
