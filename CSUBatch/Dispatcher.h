//
//  Dispatcher.h
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//

#ifndef CSUBATCH_DISPATCHER_H
#define CSUBATCH_DISPATCHER_H
#include "main.h"
#include "Job.h"

Job* current_job;
bool signal_job_completed_flag; // The dispatcher will always set this to false when a job is completed.
bool signal_on_job_completion; //This flag indicates that the dispatcher should lock the queue and signal when a job is completed.
void* run_dispatcher(void *data);

#endif //CSUBATCH_DISPATCHER_H
