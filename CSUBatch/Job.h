//
//  Job.h
//  CSUBatch
//
//  Created by Michael Moore on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
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

}Job;

//Allocates memory for a job. Returns pointer to memory location.
Job* create_job(char* name, int time, int priority);

//Frees memory after usage
void free_job(Job* job);

void job_string(Job* job, char* string);


#endif //CSUBATCH_JOB_H
