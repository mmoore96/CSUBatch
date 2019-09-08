//
// Created by trcoo on 9/3/19.
//

#include "Scheduler.h"
#include <stdio.h>
#include <pthread.h>


void* run_scheduler(void *_data){
    printf("Scheduler thread created\n");
    thread_data_t *data;
    data = (thread_data_t*)_data;
    int id = data->tid;

    while (*data->active){
        sleep(2);
    }
    printf("Terminating Scheduler\n");
    return NULL;
}