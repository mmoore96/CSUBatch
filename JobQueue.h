//
// Created by trcoo on 9/5/19.
//

#ifndef CSUBATCH_JOBQUEUE_H
#define CSUBATCH_JOBQUEUE_H

#include <stdlib.h>
#include "Job.h"
#include "Errors.h"
#include "Dispatcher.h"

//The job queue will be a linked list comprised of the following Node struct.
typedef struct Node Node;
struct Node{
    Job *job;
    Node *next;
};
//This is a global variable for holding the job queue.
//Notice the 2 leading underscores indicating it should be private. It is not advised to touch this variable
//outside of JobQueue.c/h. To interact with the job queue from CommandLineParser or any other module, call create_job_queue,
//and use the following functions to interact.
//NOTE: Even when no jobs are queue, __job_queue will point to a valid Node whose 'next' and 'job' members are null.
//As a result, when adding a job to an EMPTY queue, it is not necessary to create a new node, because job_queue will always have one,
//it is only necessary to set the 'job' member of the existing __job_queue node to the new job.
Node* __job_queue;

//The following functions operate on Node types.
int create_job_queue();
Node** get_queue();
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