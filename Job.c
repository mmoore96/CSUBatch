//
// Created by trcoo on 9/3/19.
//

#include "Job.h"
#include <stdio.h>

//Allocates memory for a job. Returns pointer to memory location.
Job* create_job(char* name, int time, int priority){
    Job* job = malloc(sizeof(Job));
    job->name = malloc(ARGUMENT_SIZE);
    strncpy(job->name, name, ARGUMENT_SIZE);
    job->time = time;
    job->priority = priority;
    return job;
}

//Frees memory after usage
void free_job(Job* job){
    free(job->name);
    free(job);
}


//Formats a string containing 'job's information, and places it in 'string'
void job_string(Job* job, char* string){
    sprintf(string, "Name %s, Time %d, Priority %d", job->name, job->time, job->priority);
}