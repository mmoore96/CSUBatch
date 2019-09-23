//
// Created by trcoo on 9/3/19.
//

#ifndef CSUBATCH_SCHEDULER_H
#define CSUBATCH_SCHEDULER_H

#include "main.h"
#include "JobQueue.h"
#include "unistd.h"
#include "SchedulingPolicies.h"

//An array for holding job pointers waiting to be added to the queue
Job* job_buffer[100];
//sort_flag is checked by the Scheduler thread to know when to sort.
//the sort method shouldn't be called directly from the commandlineparser because that module runs on the main thread,
//and sorting requires that the job queue is locked, but the main thread should be separate from needing to lock
//muteces, so the CLP module instead sets a flag that is checked by the Scheduler thread.
bool sort_flag;

//The function below is used to compare two jobs based on any given policy and is used to sort the queue.
//It should be set to point to one of the functions in SchedulingPolicies.h
int (*schedule_comparator)(Job, Job);
void* run_scheduler(void *data);
void post(Job* job);
void set_scheduling();
void insert(Node* job);
void insert_aux(Node* new_node, Node** current_node);
void sort();
void get_policy(char policy[]);


#endif //CSUBATCH_SCHEDULER_H
