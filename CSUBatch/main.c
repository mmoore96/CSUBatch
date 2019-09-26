//
//  main.c
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//
//updated with git and xcode

#include "main.h"
#include <stdio.h>
#include "CommandLineParser.h"
#include "Analytics.h"
#include <pthread.h>
#include <stdlib.h>

/* create thread argument struct for thr_func() */
//TODO: Whenever the mutex is locked, a global variable lock_owner must be updated. Failing to do so can cause difficult to find bugs,
//TODO: As a result, a function should be written that locks the mutex and then updates the variable at once. Same for unlocked

int main(int argc, char **argv) {
    //The following two globals should might as well be defined with their declarations, but for some reason doing so results in a multiple definitions compilation error. So they are defined here at runtime.
    UNOWNED = 0;
    total_number_of_jobs=0;
    starting_time = time(NULL);
    turnaround_time = 0;
    CPU_time = 0;
    waiting_time = 0;
    srand(time(NULL));
    time_ptr = malloc(9);
    MAIN = pthread_self();
    int NUM_THREADS = 2;
    pthread_t thr[NUM_THREADS];
    int i;
    pthread_mutex_init(&queue_mutex, NULL);
    pthread_cond_init(&queue_cond, NULL);
    create_job_queue();
    /* create a thread_data_t argument array */
    bool active = true;
    thread_data_t thr_data[NUM_THREADS];
    thr_data[0].active = &active;
    thr_data[1].active = &active;

    /* create threads for scheduler and dispatcher*/
    pthread_create(&thr[0], NULL, run_scheduler, &thr_data[0]);
    pthread_create(&thr[1], NULL, run_dispatcher, &thr_data[1]);

    setbuf(stdout, 0);
    start_ui();
    free(time_ptr);
    printf("Waiting for threads to join...\n");
    active = false;
    /* block until all threads complete */
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
    }
    printf("Both threads joined; Terminating main.");

    return EXIT_SUCCESS;
}

char* get_time(){
    time_t t = time(NULL);
    struct tm t1 = *localtime(&t);
    sprintf(time_ptr, "%02d:%02d:%02d", t1.tm_hour, t1.tm_min, t1.tm_sec);
    return time_ptr;
}
