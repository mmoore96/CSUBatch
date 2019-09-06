//
// Created by trcoo on 9/5/19.
//

#ifndef CSUBATCH_JOBQUEUE_H
#define CSUBATCH_JOBQUEUE_H

#include <stdlib.h>
#include "Job.h"

struct Node{
    Job *job;
    struct Node *next;

};

//TODO: Is a struct for JobQueue necessary? We really just need a reference to the first Node and we can access the entire
//TODO: list. Also the length can be easily calculated when needed.
typedef struct{
    struct Node *first;
    int length;

}JobQueue;

Job* get_first(JobQueue* q);
Job* get_job(JobQueue* q, int i);
Job* get_job_aux(struct Node* n, int i);
Job pop(JobQueue* q);
void free_jobs(JobQueue* q);
void free_jobs_aux(struct Node* n);
void push(JobQueue* q, Job* job);
int length(JobQueue* q);

#endif //CSUBATCH_JOBQUEUE_H
