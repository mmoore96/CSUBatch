//
// Created by trcoo on 9/3/19.
//

#include "Dispatcher.h"
#include "Scheduler.h"
#include <stdio.h>

void* run_dispatcher(void *_data){
    printf("Dispatcher thread created\n");
    thread_data_t *data;
    data = (thread_data_t*)_data;
    int id = data->tid;

    while (*data->active){
        sleep(2);
    }

    printf("Terminating Dispatcher\n");
    return NULL;
}