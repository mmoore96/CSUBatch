//
// Created by trcoo on 9/3/19.
//

#include "Dispatcher.h"
#include "Scheduler.h"
#include "Analytics.h"
#include <stdio.h>
#include <sys/wait.h>

void* run_dispatcher(void *_data){
    DISPATCHER = pthread_self();
    time_t job_end_time;

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
            job_start_time = time(NULL);
            if (fork() == 0){
                execv(args[0], args);
            }else{
                wait(NULL);
                current_job = NULL;
            }
            CPU_time = CPU_time + (float)(time(NULL) - job_start_time);
        }else{
            lock_owner = UNOWNED;
            job_end_time = time(NULL);
            pthread_cond_wait(&queue_cond, &queue_mutex);
            pthread_mutex_unlock(&queue_mutex);
            waiting_time = waiting_time + (float)(time(NULL) - job_end_time); //Add idling time to global
        }
    }

    printf("Terminating Dispatcher\n");
    free(current_job);
    return NULL;
}

