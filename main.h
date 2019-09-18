//
// Created by trcoo on 9/7/19.
//

#ifndef CSUBATCH_MAIN_H
#define CSUBATCH_MAIN_H
#include <stdbool.h>
#include <pthread.h>

pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;

typedef struct{
    int tid;
    bool* active;
}thread_data_t;

#endif //CSUBATCH_MAIN_H
