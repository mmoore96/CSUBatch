//
//  main.h
//  CSUBatch
//
//  Created by Michael Moore on 9/9/19.
//  Copyright © 2019 George Moore. All rights reserved.
//
#ifndef CSUBATCH_MAIN_H
#define CSUBATCH_MAIN_H
#include <stdbool.h>
#include <pthread.h>

pthread_mutex_t mutex;

typedef struct{
    int tid;
    bool* active;
}thread_data_t;

#endif //CSUBATCH_MAIN_H
