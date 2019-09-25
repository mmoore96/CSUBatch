//
//  Scheduler.h
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//

#ifndef CSUBATCH_SCHEDULER_H
#define CSUBATCH_SCHEDULER_H

#include "main.h"
#include "JobQueue.h"
#include "unistd.h"
#include "SchedulingPolicies.h"

//An array for holding job pointers waiting to be added to the queue
Job* job_buffer[100];
pthread_mutex_t buffer_mutex; //Used to lock job_buffer when accessed by main thread or scehduler thread.
pthread_cond_t buffer_cond; //Used by the main thread to indicate that a new job has been added to the buffer
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
