//
//  SchedulingPolicies.h
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/9/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//

#ifndef CSUBATCH_SCHEDULINGPOLICIES_H
#define CSUBATCH_SCHEDULINGPOLICIES_H
#include "Job.h"

//Compares two jobs based on priority.
//Returns 1 if j1 is greater, 0 if equal, -1 if j2 is greater.
int compare_priority(Job j1, Job j2);

//Compares two jobs based on execution time.
//Returns 1 if j1 is greater, 0 if equal, -1 if j2 is greater.
int compare_duration(Job j1, Job j2);

//Compares two jobs based on age
//Returns 1 if j1 is greater, 0 if equal, -1 if j2 is greater.
int compare_age(Job j1, Job j2);

#endif //CSUBATCH_SCHEDULINGPOLICIES_H
