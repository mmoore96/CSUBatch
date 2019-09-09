//
//  main.c
//  CSUBatch
//
//  Created by Michael Moore on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//
//updated with git and xcode
#include "main.h"
#include <stdio.h>
#include "CommandLineParser.h"
#include <pthread.h>
#include <stdlib.h>
#include "Dispatcher.h"
#include "Scheduler.h"
/* create thread argument struct for thr_func() */
//pthread_mutex_t mutex;
//typedef struct{
//    int tid;
//    bool* active;
//}thread_data_t;

int main(int argc, char **argv) {
    

    int NUM_THREADS = 2;
    pthread_t thr[NUM_THREADS];
    int i;
    pthread_mutex_init(&mutex, NULL);
    /* create a thread_data_t argument array */
    bool active = true;
    thread_data_t thr_data[NUM_THREADS];
    thr_data[0].active = &active;
    thr_data[0].tid = 0;
    thr_data[1].active = &active;
    thr_data[1].tid = 1;

    /* create threads for scheduler and dispatcher*/
    pthread_create(&thr[0], NULL, run_scheduler, &thr_data[0]);
    pthread_create(&thr[1], NULL, run_dispatcher, &thr_data[1]);
    start_ui();
    printf("Waiting for threads to join...\n");
    active = false;
    /* block until all threads complete */
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
    }
    printf("Both threads joined; Terminating main.");

    return EXIT_SUCCESS;

}
