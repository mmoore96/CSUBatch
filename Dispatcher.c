//
// Created by trcoo on 9/3/19.
//

#include "Dispatcher.h"
#include "Scheduler.h"
#include "Analytics.h"
#include "main.h"
#include <stdio.h>
#include <sys/wait.h>

void* run_dispatcher(void *_data){
    time_t start_idle;
    time_t job_end_time;
    char time_end[8];
    struct tm t;

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
        if (job_queue_length() > 0){
            Job job = dequeue();
            pthread_cond_signal(&queue_cond);
            current_job = &job;
            pthread_mutex_unlock(&queue_mutex);
            sprintf(args[1], "%d", job.duration);
            job_start_time = time(NULL);
            sprintf(time_end, "%s", get_time(job.duration));
            printf("[DISPATCH] Executing %s at %s\n\t Estimated job end time: %s\n", job.name, get_time(0), time_end);
            if (fork() == 0){
                execv(args[0], args);
            }else{
                wait(NULL);
                current_job = NULL;
                job_end_time = time(NULL);
                t = *localtime(&job_end_time);
                printf("[DISPATCH] Job %s completed at %s\n\n", job.name, get_time(0));
            }
            //Lock the queue and signal to the main thread that a job has been completed.
            if (signal_on_job_completion) {
                pthread_mutex_lock(&queue_mutex);
                pthread_cond_signal(&queue_cond);
                pthread_mutex_unlock(&queue_mutex);
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

