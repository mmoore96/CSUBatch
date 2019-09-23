//
// Created by trcoo on 9/3/19.
//

#ifndef CSUBATCH_DISPATCHER_H
#define CSUBATCH_DISPATCHER_H
#include "main.h"
#include "Job.h"

Job* current_job;
void* run_dispatcher(void *data);

#endif //CSUBATCH_DISPATCHER_H
