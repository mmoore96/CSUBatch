//
//  SchedulingPolicies.c
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/9/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//

#include "SchedulingPolicies.h"

int compare_priority(Job j1, Job j2){
    if (j1.priority > j2.priority){
        return 1;
    }else if (j1.priority == j2.priority){
        return 0;
    } else{
        return -1;
    }

}

int compare_duration(Job j1, Job j2){
    if (j1.duration < j2.duration){
        return 1;
    }else if (j1.duration == j2.duration){
        return 0;
    } else{
        return -1;
    }
}

int compare_age(Job j1, Job j2){
    if (j1.age < j2.age){
        return 1;
    } else if (j1.age == j2.age){
        return 0;
    } else{
        return -1;
    }
}
