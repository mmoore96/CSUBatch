//
// Created by trcoo on 9/7/19.
//

#ifndef CSUBATCH_MAIN_H
#define CSUBATCH_MAIN_H
//The following are used with lock_owner to indicate what thread owns a lock.
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;
//Indicates the current owner of the mutex lock
char* time_ptr;
//Checked by the threads to know if the process is still running
bool active;


char* get_time(int job_time);


#endif //CSUBATCH_MAIN_H
