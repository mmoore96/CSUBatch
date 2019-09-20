//
// Created by trcoo on 9/3/19.
//

#include "Job.h"
#include <stdio.h>

//Allocates memory for a job. Returns pointer to memory location.
Job* create_job(char* name, int duration, int priority){
    Job* job = malloc(sizeof(Job));
    job->name = malloc(ARGUMENT_SIZE);
    strncpy(job->name, name, ARGUMENT_SIZE);
    job->duration = duration;
    job->priority = priority;
    job->creation_time = time(0);
    return job;
}

//Frees memory after usage
void free_job(Job* job){
    free(job->name);
    free(job);
}


//Formats a string containing 'job's information, and places it in 'string'
void job_string(Job* job, char* string){
    sprintf(string, "%s\t%d\t%d\t%ld", job->name, job->duration, job->priority, job->creation_time);
}