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

int main(int argc, char **argv) {
    //Initialize globals
    total_number_of_jobs=0;
    starting_time = time(NULL);
    turnaround_time = 0;
    CPU_time = 0;
    waiting_time = 0;
    srand(time(NULL));
    time_ptr = malloc(9);

    int NUM_THREADS = 2;
    pthread_t thr[NUM_THREADS];
    int i;
    pthread_mutex_init(&queue_mutex, NULL);
    pthread_cond_init(&queue_cond, NULL);
    create_job_queue();
    active = true;

    /* create threads for scheduler and dispatcher*/
    pthread_create(&thr[0], NULL, run_scheduler, NULL);
    pthread_create(&thr[1], NULL, run_dispatcher, NULL);

    //Allow for debuggin (only necessary on windows, no effect on linux
    setbuf(stdout, 0);

    //Begin main process
    start_ui();

    //Free pointer to time variable
    free(time_ptr);

    printf("[MAIN] Waiting for threads to join...\n");
    //Set thread condition to end
    active = false;
    /* block until all threads complete */
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
    }
    printf("[MAIN] Both threads joined; Terminating main.");

    return EXIT_SUCCESS;
}

/// Get's the current time and formats it as a string.
/// \param job_time | If provided, the string returned will be the current time plus the job time.
/// \return | A pointer to the string containing the time.
char* get_time(int job_time){
    time_t t = time(NULL) + (time_t)job_time;
    struct tm t1 = *localtime(&t);
    sprintf(time_ptr, "%02d:%02d:%02d", t1.tm_hour, t1.tm_min, t1.tm_sec);
    return time_ptr;
}
