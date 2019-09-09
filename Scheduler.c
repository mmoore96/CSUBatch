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
    int id = data->tid;

    while (*data->active){
        sleep(2);
    }
    printf("Terminating Scheduler\n");
    return NULL;
}

void post(Job* job){
    if (!schedule_comparator){
        schedule_comparator = &compare_age;
    }
    if (schedule_comparator == &compare_age || job_queue_length() == 0){
        enqueue(job);   //If first come first serve scheduling is enabled we can just tack this job on the queue
    } else {
        insert(job, get_queue());
    }
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

void insert(Job* job, Node* q){
    if (schedule_comparator(*job, *q->job) < 0){
        if (schedule_comparator(*job, *q->next->job)) {
            insert(job, q->next);
        } else{
            Node* new_node = malloc(sizeof(Node));
            new_node->job = job;
            new_node->next = q->next;
            q->next = new_node;
        }
    }else{
        Node* new_node = malloc(sizeof(Node));
        new_node->job = job;
        new_node->next = get_queue()->next;
        get_queue()->next = new_node;
    }
}