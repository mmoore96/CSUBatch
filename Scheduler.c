//
// Created by trcoo on 9/3/19.
//

#include "Scheduler.h"
#include "JobQueue.h"
#include <stdio.h>
#include <pthread.h>


void* run_scheduler(void *_data){
    thread_data_t *data;
    data = (thread_data_t*)_data;
    //Set the default policy to first come first serve by setting the comparator to SchedulingPolicies::compare_age
    schedule_comparator = &compare_age;
    int id = data->tid;

    while (*data->active){

    }
    printf("Terminating Scheduler\n");
    return NULL;
}

void post(Job* job){
    insert(job);
}

void set_priority_scheduling(){
    schedule_comparator = &compare_priority;
}

void set_fcfs_scheduling(){
    schedule_comparator = &compare_age;
}

void set_sjf_scheduling(){
    schedule_comparator = &compare_duration;
}

void insert(Job* job){
    if (job_queue_length() == 0){
        //If the job queue is empty, just set the job member of the queue to the given job.
        *get_queue()->job = job;
        //TODO: RESUME WORKING HERE,
    } else {
        insert_aux(job, *get_queue());
    }
}

//A recursive helper function for insert.
//It is initially called by insert and the node given should refer to the beginning of the queue.
//Each recursive call passes in the next node after the on passed in, so that the job is compared against each
//node in the queue
void insert_aux(Job* job, Node* q){
    if (schedule_comparator(*job, *q->job) < 0){
        if (schedule_comparator(*job, *q->next->job)) {
            insert_aux(job, q->next);
        } else{
            Node* new_node = malloc(sizeof(Node));
            new_node->job = job;
            new_node->next = q->next;
            q->next = new_node;
        }
    }else{
        Node* new_node = malloc(sizeof(Node));
        new_node->job = job;
        new_node->next = get_queue();


        //get_queue()->next = new_node;

    }
}