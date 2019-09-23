//
// Created by trcoo on 9/5/19.
//

#include "JobQueue.h"
#include "Scheduler.h"
#include <stdio.h>

int create_job_queue(){
    __job_queue = malloc(sizeof(Node*));
    return 0;
}


//Returns a pointer to the pointer to the job_queue.
//This is used to change where the pointer points when the next node in the queue should be changed.
Node** get_queue(){
    return __job_queue;
}

//Places the address of the job at index 'index' into 'job'
//Returns 0 if successful
Job* get_job(int index){
    return __get_job_aux(index, *__job_queue);
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
    return __get_node_aux(index, *__job_queue);
}

Node* __get_node_aux(int index, Node* q){
    if (index == 0){
        return q;
    }else if (q->next != NULL){
        return __get_node_aux(index - 1, q->next);
    }else{
        return NULL;
    }
}

Job* get_last_job(){
    return get_job(job_queue_length()-1);
}


Node* get_last_node(){
    return get_node(job_queue_length()-1);
}

//Removes last Job from queue and returns it
Job dequeue(){
    Node* next_node = *get_queue(); //This is the node from which the job will be extracted, then the node will be freed
    Job next_job = *next_node->job; //This is the job to be removed and returned
    if (job_queue_length() == 1){
        free(next_node->job);
        free(next_node);
        *get_queue() = NULL;
        return next_job;
    }else{
        *get_queue() = (*get_queue())->next;
        free(next_node->job);
        free(next_node);
        return next_job;
    }
}

//Adds 'job' to the end of the queue
//Returns exit status; 0 if success
//To add a new node, we set the new node's 'next' to be the current first node, and then set our
//reference to the first node to be the new node.
//TODO: Consider removing this function
int enqueue(Job *job){
    if (job_queue_length(__job_queue) == 0){
        (*__job_queue)->job = job;
        return 0;
    }else {
        Node* new_node = malloc(sizeof(Node));  //Allocate memory for new node
        if (new_node) {
            get_last_node()->next = new_node;
            new_node->job = job;   //Set the job of new node.
            new_node->next = NULL;

            return 0;
        }else{
            return UNABLE_TO_ALLOCATE_MEMORY;
        }
    }
}


//This function sets the 'next' pointer for every node to NULL. This makes it easier to sort the job queue
//Before this function is called, all Node*'s should be copied to an array, then the nodes have their 'next's cleared,
//then you can use insert(Node*) for each Node* to reorder the queue
void clear_node_links(){
    __clear_node_links_aux(*get_queue());
    (*get_queue()) = NULL;
}

void __clear_node_links_aux(Node* n){
    if (n != NULL){
        __clear_node_links_aux(n->next);
        n->next = NULL;
    }
}

void free_job_queue(){
    __free_job_queue_aux(*__job_queue);
    free(__job_queue);
}

void __free_job_queue_aux(Node* n){
    if (n != NULL) {
        __free_job_queue_aux(n->next);
        printf("NODE POINTER %p FREED\n", (void*) n);
        printf("JOB->NAME POINTER %p FREED\n", (void*) n->job->name);
        printf("JOB POINTER %p FREED\n", (void*) n->job);
        free_job(n->job);
        free(n);
    }
}

int job_queue_length(){
    if (lock_owner != pthread_self()){
        // Lock the mutex IF AND ONLY IF the current thread does not already have the lock
        pthread_mutex_lock(&queue_mutex);
        lock_owner = pthread_self();
    }
    if (*__job_queue == NULL){
        lock_owner = UNOWNED;
        pthread_mutex_unlock(&queue_mutex);
        return 0;
    }else{
        return __job_queue_length_aux(1, (*__job_queue)->next);
    }
}

int __job_queue_length_aux(int count, Node* q){
    if (q == NULL){
        return count;
    } else{
        return __job_queue_length_aux(count + 1, q->next);
    }
}

void print_job_queue(){
    Job job;
    int length = job_queue_length();
    char policy[6];
    get_policy(policy);
    printf("Total number of jobs in the queue: %d\n", length + ((current_job != NULL) ? 1 : 0));
    printf("Scheduling Policy: %s\n", policy);
    printf("Name    \tCPU_Time\tPriority\tArrival\tProgress\n");
    if (current_job != NULL){
        job = *current_job;
        printf("%-12s%-12d%-12d%s\tRunning\n", job.name, job.duration, job.priority, job.arrival_time);
    }
    for (int i = 0; i < length; i++)
    {
        job = *get_job(i);
        printf("%-12s%-12d%-12d%s\n", job.name, job.duration, job.priority, job.arrival_time);
    }
}

