//
//  main.c
//  CSUBatch
//
//  Created by Michael Moore on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//

#include <stdio.h>
#include "CommandLineParser.h"
#include <stdlib.h>
#include <pthread.h>
#include "Dispatcher.h"
#include "Scheduler.h"
/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid;
  double stuff;
}

thread_data_t;
 
    int main(int argc, char **argv) {
        //start_ui();
        int NUM_THREADS = 1;
        pthread_t thr[NUM_THREADS];
        int i, rc;
      /* create a thread_data_t argument array */
        thread_data_t thr_data[NUM_THREADS];
     
      /* create threads */
        pthread_create(&thr[i], NULL,schuduler_main, &thr_data[i]);
        pthread_create(&thr[i], NULL,dispatcher_main, &thr_data[i]);
        start_ui();
      /* block until all threads complete */
      for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
      }
     
      return EXIT_SUCCESS;
    
    }
    

