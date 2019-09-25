//
// Created by trcoo on 9/3/19.
//

#include "Job.h"
#include <stdio.h>

/// Allocates memory for a job
/// \param name | Name of job
/// \param duration | Job duration
/// \param priority | Job priority
/// \return | Pointer to the newly allocated and initialized job.
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

/// Free job memory.
/// \param job | Job to free.
void free_job(Job* job){
    free(job->name);
    free(job->arrival_time);
    free(job);
}

