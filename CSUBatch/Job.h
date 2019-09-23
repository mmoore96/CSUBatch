//
//  Job.h
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//

#ifndef CSUBATCH_JOB_H
#define CSUBATCH_JOB_H
#include <stdlib.h>
#include "Constants.h"
#include <string.h>
#include <time.h>

typedef struct{
    char* name;
    int priority;
    int duration;
    time_t age;
    char* arrival_time;

}Job;

//Allocates memory for a job. Returns pointer to memory location.
Job* create_job(char* name, int time, int priority);

//Frees memory after usage
void free_job(Job* job);

#endif //CSUBATCH_JOB_H
