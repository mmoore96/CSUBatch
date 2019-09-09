//
//  Dispatcher.c
//  CSUBatch
//
//  Created by Michael Moore on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//

#include "Dispatcher.h"
#include "Scheduler.h"
#include <stdio.h>
//#include "main.c"

void* run_dispatcher(void *_data){
    thread_data_t *data;
    data = (thread_data_t*)_data;
    int id = data->tid;

    while (*data->active){
        sleep(2);
    }

    printf("Terminating Dispatcher\n");
    return NULL;
}
