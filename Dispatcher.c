//
// Created by trcoo on 9/3/19.
//

#include "Dispatcher.h"
#include "Scheduler.h"
#include <stdio.h>
#include <sys/wait.h>

void* run_dispatcher(void *_data){
    DISPATCHER = pthread_self();
    //current_job = malloc(sizeof(Job));

    thread_data_t *data;
    data = (thread_data_t*)_data;
    //Define an array of two strings. The first string holds the execution time of the job, which will be passed
    //to batch_job as a program argument. the second argument is null, because execv requires that the parameter
    //array be null terminated.
    char job_duration[10];
    char* args[3];
    args[0] = "batch_job";
    args[1] = job_duration;
    args[2] = NULL;

    while (*data->active){
        pthread_mutex_lock(&queue_mutex);
        lock_owner = pthread_self();
        if (job_queue_length() > 0){
            Job job = dequeue();
            current_job = &job;
            lock_owner = UNOWNED;
            pthread_mutex_unlock(&queue_mutex);
            sprintf(args[1], "%d", job.duration);
            if (fork() == 0){
                execv(args[0], args);
            }else{
                wait(NULL);
                current_job = NULL;
            }
        }else{
            lock_owner = UNOWNED;
            pthread_mutex_unlock(&queue_mutex);
            //TODO: Use pthread_cond_wait here to wait for the main thread to produce a new job instead of constantly checking for a new job
        }
    }

    printf("Terminating Dispatcher\n");
    free(current_job);
    return NULL;
}

