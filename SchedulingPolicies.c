//
// Created by trcoo on 9/8/19.
//

#include "SchedulingPolicies.h"

/// Compares two jobs by priority
/// \param j1 | Job 1
/// \param j2 | Job 2
/// \return | 1 if j1>j2, 0 if j1==j2, -1 if j1<j2
int compare_priority(Job j1, Job j2){
    if (j1.priority > j2.priority){
        return 1;
    }else if (j1.priority == j2.priority){
        return 0;
    } else{
        return -1;
    }

}

/// Compares two jobs by execution time
/// \param j1 | Job 1
/// \param j2 | Job 2
/// \return | 1 if j1>j2, 0 if j1==j2, -1 if j1<j2
int compare_duration(Job j1, Job j2){
    if (j1.duration < j2.duration){
        return 1;
    }else if (j1.duration == j2.duration){
        return 0;
    } else{
        return -1;
    }
}

/// Compares two jobs by age
/// \param j1 | Job 1
/// \param j2 | Job 2
/// \return | 1 if j1>j2, 0 if j1==j2, -1 if j1<j2
int compare_age(Job j1, Job j2){
    if (j1.age < j2.age){
        return 1;
    } else if (j1.age == j2.age){
        return 0;
    } else{
        return -1;
    }
}
