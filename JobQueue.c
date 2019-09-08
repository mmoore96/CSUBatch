//
// Created by trcoo on 9/5/19.
//

#include "JobQueue.h"
#include <stdio.h>

int create_job_queue(){
    __job_queue = malloc(sizeof(Node));
    __job_queue->next = NULL;
    __job_queue->job = NULL;
    return 0;
}


Job* get_first(){
    if (__job_queue->job){
        return __job_queue->job;
    }else{
        return NULL;
    }
}

//Places the address of the job at index 'index' into 'job'
//Returns 0 if successful
Job* get_job(int index){
    return __get_job_aux(index, __job_queue);
}

Job* __get_job_aux(int index, Node* n){
    if (index == 0){
        return n->job;
    }else if (n->next != NULL){
        return __get_job_aux(index - 1, n->next);
    }else{
        return NULL;
    }
}

Node* get_node(int index){
    return __get_node_aux(index, __job_queue);
}

Node* __get_node_aux(int index, Node* q){
    if (index == 0){
        return q;
    }else if (q->next != NULL){
        return __get_node_aux(index, q->next);
    }else{
        return NULL;
    }
}

Job* get_last_job(){
    return get_job(job_queue_length()-2);
}


Node* get_last_node(){
    return get_node(job_queue_length()-2);
}

//Removes oldest Job from queue and returns it
Job* dequeue(){
    if (__job_queue->job == NULL){
        return NULL;
    }else{
        Node* second_last_node = get_node(job_queue_length() - 2);
        Job* last_job = get_last_job();
        second_last_node->next = NULL;
        free(second_last_node->next);
        return last_job;
    }
}

//Adds 'job' to the beginning of the queue
//Returns exit status; 0 if success
//To add a new node, we set the new node's 'next' to be the current first node, and then set our
//reference to the first node to be the new node.
int enqueue(Job *job){
    if (job_queue_length(__job_queue) == 0){
        __job_queue->job = job;
        return 0;
    }else {
        Node* new_node = malloc(sizeof(Node));  //Allocate memory for new node
        if (new_node) {
            new_node->job = __job_queue->job;   //Set the job of new node.
            new_node->next = __job_queue->next; //Set the next node of new node to be the current first node of the queue
            __job_queue->next = new_node;
            __job_queue->job = job;

            return 0;
        }else{
            return UNABLE_TO_ALLOCATE_MEMORY;
        }
    }
}

int free_job_queue(){
    return __free_jobs_aux(__job_queue);
}

int __free_jobs_aux(Node* n){
    if (n != NULL) {
        __free_jobs_aux(n->next);
        printf("NODE POINTER %p FREED\n", (void*) n);
        printf("JOB->NAME POINTER %p FREED\n", (void*) n->job->name);
        printf("JOB POINTER %p FREED\n", (void*) n->job);
        free_job(n->job);
        free(n);
    }
    return 0;
}

int job_queue_length(){
    if (__job_queue == NULL || __job_queue->job == NULL){
        return 0;
    }else{
        return __job_queue_length_aux(1, __job_queue);
    }
}

int __job_queue_length_aux(int count, Node* q){
    if (q->next == NULL){
        return count;
    } else{
        return __job_queue_length_aux(count + 1, q->next);
    }
}
