//
// Created by trcoo on 9/5/19.
//

#include "JobQueue.h"
#include "Scheduler.h"
#include "Analytics.h"
#include <stdio.h>

/// Allocates memory for the job queue. Should be called in main.
/// \return |
void create_job_queue(){
    __job_queue = malloc(sizeof(Node*));
}


/// Used to get a reference to the job queue.
/// \return | Returns a double pointer to the job queue, in which, when dereferenced once, returns a pointer to the first node.
Node** get_queue(){
    return __job_queue;
}

/// Returns the job at the given index
/// \param index | The index of the desired job
/// \return | The node to be returned
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

/// Returns the node at the given index
/// \param index | The index of the desired node
/// \return | The node to be returned
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

///Removes last Job from the queue and returns it
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


///Clears the queue. When sorting, the contents of the queue should be copied, then the queue cleared, then the contents reinserted.
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
///Frees the memory of all jobs and nodes.
void free_job_queue(){
    __free_job_queue_aux(*__job_queue);
    free(__job_queue);
}

void __free_job_queue_aux(Node* n){
    if (n != NULL) {
        __free_job_queue_aux(n->next);
        free_job(n->job);
        free(n);
    }
}


///Returns the number of jobs in the queue. Does NOT include a job being executed.
int job_queue_length(){
    return __job_queue_length_aux(*__job_queue);
}

int __job_queue_length_aux(Node* q){
    if (q == NULL){
        return 0; //Count the current job being executed if it exists
    } else{
        return 1 + __job_queue_length_aux(q->next);
    }
}

///Prints the job queue.
void print_job_queue(){
    Job job;
    int length = job_queue_length();
    char policy[6]; //The space for the policy string, which will be either "sjf", "FCFS", or "priority".
    get_policy(policy);
    printf("Total number of jobs waiting for dispatch: %d\n", length);
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

///Adds up the duration of every job in the queue.
int job_queue_time(){
    pthread_mutex_lock(&queue_mutex);
    return __job_queue_time_aux(*get_queue());
}

int __job_queue_time_aux(Node* node){
    if (node == NULL){
        int current_job_time = 0; //The remaining time of a job running right now
        if (current_job != NULL){
            current_job_time = current_job->duration - (int)(time(NULL) - job_start_time);
        }
        pthread_mutex_unlock(&queue_mutex);
        return current_job_time;
    } else{
        return node->job->duration + __job_queue_time_aux(node->next);
    }
}