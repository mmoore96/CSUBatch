//
//  Scheduler.h
//  CSUBatch
//
//  Created by Michael Moore on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//

#ifndef CSUBATCH_SCHEDULER_H
#define CSUBATCH_SCHEDULER_H

#include "main.h"
#include "JobQueue.h"
#include "unistd.h"
#include "SchedulingPolicies.h"
#define fcfs_enum 0
#define sjf_num 1
#define priority_num 2


int (*schedule_comparator)(Job, Job);
void* run_scheduler(void *data);
void post(Job* job);
void set_priority_scheduling(void);
void set_fcfs_scheduling(void);
void set_sjf_scheduling(void);
void insert(Job* job, Node* q);


#endif //CSUBATCH_SCHEDULER_H
