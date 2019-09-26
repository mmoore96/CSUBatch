//
//  main.h
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
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
#include <stdio.h>

pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;
//Indicates the current owner of the mutex lock
unsigned long lock_owner;
unsigned long buffer_owner;
char scheduling_policy[4];
char* time_ptr;


typedef struct{
    bool* active;
}thread_data_t;

char* get_time();


#endif //CSUBATCH_MAIN_H
