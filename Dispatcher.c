//
// Created by trcoo on 9/3/19.
//

#include "Dispatcher.h"
#include "Scheduler.h"
#include <stdio.h>

void* run_dispatcher(void *_data){
    thread_data_t *data;
    data = (thread_data_t*)_data;
    //Define an array of two strings. The first string holds the execution time of the job, which will be passed
    //to batch_job as a program argument. the second argument is null, because execv requires that the parameter
    //array be null terminated.
    char job_duration[10];
    char* args[2];
    args[0] =  job_duration;
    args[1] = NULL;

    while (*data->active){
        pthread_mutex_lock(&queue_mutex);
        if (job_queue_length() > 0){
            Job job = dequeue();
            pthread_mutex_unlock(&queue_mutex);
            sprintf(args[0], "%d", job.duration);
            //TODO: have this thread wait until the process called by execv finishes
            int x = execv("batch_job", args);
            printf("Execv returns code: %d\n", x);
        }else{
            pthread_mutex_unlock(&queue_mutex);
            //TODO: replace sleep with pthread_cond_wait()
            sleep(1); //Wait a second if no jobs are available to improve performance.
        }
    }

    printf("Terminating Dispatcher\n");
    return NULL;
}