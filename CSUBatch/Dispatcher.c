//
//  Dispatcher.c
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//

#include "Dispatcher.h"
#include "Scheduler.h"
#include "Analytics.h"
#include "main.h"
#include <stdio.h>
#include <sys/wait.h>

void* run_dispatcher(void *_data){
    time_t start_idle;
    char time_end[9];
    //Define an array of two strings. The first string holds the execution time of the job, which will be passed
    //to batch_job as a program argument. the second argument is null, because execv requires that the parameter
    //array be null terminated.
    char job_duration[10];
    char* args[3];
    args[0] = "/Users/MichaelMoore/batchjob";
    args[1] = job_duration;
    args[2] = NULL;

    while (active){
        pthread_mutex_lock(&queue_mutex);
        if (job_queue_length() > 0){
            Job job = dequeue();
            pthread_cond_signal(&queue_cond);
            current_job = &job;
            pthread_mutex_unlock(&queue_mutex);
            sprintf(args[1], "%d", job.duration);
            job_start_time = time(NULL);
            sprintf(time_end, "%s", get_time(job.duration));
            printf("[DISPATCH] Executing %s at %s.\t Estimated job end time: %s\n", job.name, get_time(0), time_end);
            if (fork() == 0){
                execv(args[0], args);
            }else{
                wait(NULL);
                current_job = NULL;
                printf("[DISPATCH] Job %s completed at %s\n", job.name, get_time(0));
            }
            //Lock the queue and signal to the main thread that a job has been completed.
            if (signal_on_job_completion) {
                pthread_mutex_lock(&queue_mutex);
                pthread_cond_signal(&queue_cond);
                pthread_mutex_unlock(&queue_mutex);
            }else{
                printf(">");
            }


            CPU_time = CPU_time + (time(NULL) - job_start_time);

        }else{
            start_idle = time(NULL);
            pthread_cond_wait(&queue_cond, &queue_mutex);
            waiting_time = waiting_time + (time(NULL) - start_idle);
            pthread_mutex_unlock(&queue_mutex);
        }
    }

    printf("Terminating Dispatcher\n");
    free(current_job);
    return NULL;
}
