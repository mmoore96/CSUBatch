//
//  Analytics.h
//  CSUBatch
//
//  Created by Michael Moore on 9/25/19.
//  Copyright © 2019 George Moore. All rights reserved.
//

#ifndef CSUBATCH_ANALYTICS_H
#define CSUBATCH_ANALYTICS_H

//#include <bits/types/time_t.h>
#include <sys/types.h>

time_t starting_time;
int total_number_of_jobs;
float turnaround_time;
float CPU_time;
float waiting_time;
float throughput;
time_t job_start_time;



#endif //CSUBATCH_ANALYTICS_H
