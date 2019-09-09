//
//  JobQueue.h
//  CSUBatch
//
//  Created by Michael Moore on 9/9/19.
//  Copyright © 2019 George Moore. All rights reserved.
//

#ifndef CSUBATCH_JOBQUEUE_H
#define CSUBATCH_JOBQUEUE_H

#include <stdlib.h>
#include "Job.h"
#include "Errors.h"
#include "Dispatcher.h"

//Wish I could typedef this to remove need to prefix ever JobQueue delcaration with struct,
//But doing so causes issues with the 'next' member delcaration
typedef struct Node Node;
struct Node{
    Job *job;
    Node *next;
};
//This is a global variable for holding the job queue.
//Notice the 2 leading underscores indicating it should be private. It is not advised to touch this variable
//outside of JobQueue.c/h. To interact with the job queue from CommandLineParser or any other module, call create_job_queue
//with a JobQueue pointer. The global job queue will be placed in the pointer.
Node* __job_queue;

//The following functions operate on JobQueue types.
//Note that for functions intended to get a job object, the last parameter is the pointer
//pointing to the job being received.
//Functions that return int return and exit code; and exit code of non-zero indicates an error occurred.
int create_job_queue(void);
Node* get_queue(void);
Job* get_job(int index);
Job* __get_job_aux(int index, Node* q);
Node* get_node(int index);
Node* __get_node_aux(int index, Node* q);
Job* get_last_job();
Job dequeue();
int free_job_queue();
int __free_job_queue_aux(Node* q);
int enqueue(Job* job);
int job_queue_length();
int __job_queue_length_aux(int count, Node* q);
void print_job_queue();

#endif //CSUBATCH_JOBQUEUE_H
