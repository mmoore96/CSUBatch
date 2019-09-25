//
// Created by trcoo on 9/5/19.
//

#ifndef CSUBATCH_JOBQUEUE_H
#define CSUBATCH_JOBQUEUE_H

#include <stdlib.h>
#include "Job.h"
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
//It is a double pointer so that when necessary, the pointer to the very first element can be changed.
//It's basically an array of Node*'s, except they are not in contiguous memory.
Node** __job_queue;

//The following functions operate on Node types.
void create_job_queue();
Node** get_queue();
Job* get_job(int index);
Job* __get_job_aux(int index, Node* q);
Node* get_node(int index);
Node* __get_node_aux(int index, Node* q);
Job dequeue();
void clear_node_links();
void __clear_node_links_aux(Node* n);
void free_job_queue();
void __free_job_queue_aux(Node* q);
int job_queue_length();
int __job_queue_length_aux(Node* q);
int job_queue_time();
int __job_queue_time_aux(Node* q);
void print_job_queue();

#endif //CSUBATCH_JOBQUEUE_H
