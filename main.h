//
// Created by trcoo on 9/7/19.
//

#ifndef CSUBATCH_MAIN_H
#define CSUBATCH_MAIN_H
//The following are used with lock_owner to indicate what thread owns a lock.
unsigned long UNOWNED; //I am assuming that a thread ID will never be 0 but I could be wrong.
unsigned long SCHEDULER;
unsigned long DISPATCHER;
unsigned long MAIN;
#include <stdbool.h>
#include <pthread.h>

pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;
//Indicates the current owner of the mutex lock
unsigned long lock_owner;
char scheduling_policy[4];


typedef struct{
    bool* active;
}thread_data_t;

#endif //CSUBATCH_MAIN_H
