#include "main.h"
#include <stdio.h>
#include "CommandLineParser.h"
#include <pthread.h>
#include <stdlib.h>

/* create thread argument struct for thr_func() */
//TODO: Whenever the mutex is locked, a global variable lock_owner must be updated. Failing to do so can cause difficult to find bugs,
//TODO: As a result, a function should be written that locks the mutex and then updates the variable at once. Same for unlocked

int main(int argc, char **argv) {
    UNOWNED = 0;
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
    printf("Waiting for threads to join...\n");
    active = false;
    /* block until all threads complete */
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
    }
    printf("Both threads joined; Terminating main.");

    return EXIT_SUCCESS;

}