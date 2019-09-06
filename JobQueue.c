//
// Created by trcoo on 9/5/19.
//

#include "JobQueue.h"
#include <stdio.h>

Job* get_first(JobQueue* q){
    return q->first->job;
}

Job* get_job(JobQueue* q, int i){
    return get_job_aux(q->first, i);
}

Job* get_job_aux(struct Node* n, int i){
    if (i == 0){
        return n->job;
    }else if (n->next != NULL){
        return get_job_aux(n->next, i - 1);
    }else{
        return NULL;
    }
}

Job pop(JobQueue* q){
    struct Node *first_node = q->first; //Grab the pointer to the first node in the queue
    Job first_job = *first_node->job;    //Grab a copy of the job
    q->first = q->first->next;          //Adjust the queue so it now points to the next node as first
    free(first_node);                   //Free the memory held by the old first node,
    q->length -= 1;                     //Update size
    return first_job;                   //Return job
}

void push(JobQueue* q, Job *job){
    struct Node* node_ptr = malloc(sizeof(struct Node));  //Allocate memory for new node
    printf("NODE POINTER %ld ALLOCATED", (long)node_ptr);
    node_ptr->job = job;                                  //Set the job of new node.
    node_ptr->next = q->first;                            //Set the next node of new node to be the current first node of the queue
    q->first = node_ptr;                                  //Set the first node of the queue to be the new node
    q->length += 1;                                       //Update size
}

void free_jobs(JobQueue* q){
    free_jobs_aux(q->first);
}

void free_jobs_aux(struct Node* n){
    if (n != NULL) {
        free_jobs_aux(n->next);
        printf("NODE POINTER %ld FREED", (long) n);
        printf("JOB POINTER %ld FREED", (long) n->job);
        free(n->job);
        free(n);
    }
}

int length(JobQueue* q){
    return q->length;
}
