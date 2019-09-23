//
//  Job.c
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//

#include "Job.h"
#include <stdio.h>

//Allocates memory for a job. Returns pointer to memory location.
Job* create_job(char* name, int duration, int priority){
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    Job* job = malloc(sizeof(Job));
    job->age = t;
    job->name = malloc(ARGUMENT_SIZE);
    strncpy(job->name, name, ARGUMENT_SIZE);
    job->arrival_time = malloc(8);
    sprintf(job->arrival_time, "%02d:%02d:%02d", time.tm_hour, time.tm_min, time.tm_sec);
    job->duration = duration;
    job->priority = priority;
    return job;
}

//Frees memory after usage
void free_job(Job* job){
    free(job->name);
    free(job->arrival_time);
    free(job);
}
