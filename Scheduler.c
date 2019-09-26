//
// Created by trcoo on 9/3/19.
//

#include "Scheduler.h"
#include "JobQueue.h"
#include <stdio.h>
#include <pthread.h>


void* run_scheduler(void *_data){
    pthread_mutex_init(&buffer_mutex, NULL);
    pthread_cond_init(&buffer_cond, NULL);
    sort_flag = false;
    job_added = false;
    buffer_empty = false;
    //Set the default policy to first come first serve by setting the comparator to SchedulingPolicies::compare_age
    schedule_comparator = &compare_age;
    for (int i = 0; i < 100; i ++){
        job_buffer[i] = NULL;
    }
    // Lock the buffer mutex before the loop begins
    //pthread_mutex_lock(&buffer_mutex);
    while (active){
        if (sort_flag){
            pthread_mutex_lock(&queue_mutex);
            sort();
            pthread_mutex_unlock(&queue_mutex);
            pthread_cond_signal(&queue_cond);
            sort_flag = false;
        }

        for (int i = 0; i < 100; i ++){
            pthread_mutex_lock(&buffer_mutex);
            if (job_buffer[i] != NULL){
                job_added = true;
                Node* new_node = malloc(sizeof(Node));
                new_node->job = job_buffer[i];
                new_node->next = NULL;
                job_buffer[i] = NULL;
                pthread_mutex_lock(&queue_mutex);
                insert(new_node);
                pthread_cond_signal(&queue_cond);
                pthread_mutex_unlock(&queue_mutex);
            }
            pthread_mutex_unlock(&buffer_mutex);
        }
        pthread_mutex_lock(&buffer_mutex);
        if (!job_added) {
            pthread_cond_wait(&buffer_cond, &buffer_mutex);
            // Scheduler will now have lock after wait!
        }
        if (get_buffer_size() == 0) {
            pthread_cond_signal(&buffer_cond);
            buffer_empty = true;
        }

        pthread_mutex_unlock(&buffer_mutex);

    }
    printf("[SCHEDULER] Terminating Scheduler\n");
    //Free any job pointers residing in the job buffer
    for (int i = 0; i < 100; i ++){
        if (job_buffer[i] != NULL){
            free(job_buffer[i]);
        }
    }
    return NULL;
}

/// Adds a Job to a buffer, where it waits to be inserted into the job queue by the Scheduler. This function is called from the main thread.
/// \param job | The job to be added.
void post(Job* job){
    pthread_mutex_lock(&buffer_mutex); //Lock job buffer

    //Find the first free space in the array to place the job.
    for (int i = 0; i < 100; i ++){
            if (job_buffer[i] == NULL){
                job_buffer[i] = job;
                break;
            }
        }

    pthread_cond_signal(&buffer_cond); //Signal to Scheduler that a job has been added.
    pthread_mutex_unlock(&buffer_mutex); //Unlock job buffer
}

/// Used to set the new policy, where fcfs, sjf, and priority are mapped to integers 0, 1, and 2 respectively.
///This function will be called from the main thread, which is why a flag is set to schedule a sort from the Scheduler thread
/// \param p | 0=fcfs, 1=sjf, 2=priority
void set_scheduling(int p){
    switch (p){
        case 0: schedule_comparator = &compare_age; break;
        case 1: schedule_comparator = &compare_duration; break;
        case 2: schedule_comparator = &compare_priority; break;
        default: printf("ERROR: SET_SCHEDULING FUNCTION GIVEN UNKNOWN VALUE %d!\n", p);
    }
    sort_flag = true;
    printf("[MAIN] Scheduling a policy change...\n");
    pthread_cond_signal(&buffer_cond);
}

/// Called exclusively by Scheduler thread to insert a node into the job queue using selection sort algorithm
/// \param new_node | The node to be added into the queue
void insert(Node* new_node){
    if (job_queue_length() == 0){
        *get_queue() = new_node;
    }else{
        insert_aux(new_node, get_queue());
    }
}

/// A recursive helper function. This function should be initially called from insert() with current_node being a pointer to the first node in the queue
/// \param new_node | The node to be inserted
/// \param current_node | The current node already in the job queue by which new_node is being compared.
void insert_aux(Node* new_node, Node** current_node){
    Job* new_job = new_node->job;
    Node* next_node = ((*current_node)->next); //The node after the one being compared currently
    Job selected_job = *(*current_node)->job; //The current job in the queue to which we compare the new job
    if (schedule_comparator(*new_job, selected_job) < 0){
        //Entering this block indicates that the new job has a lower priority than the current node's job.
        if (next_node != NULL && schedule_comparator(*new_job, *next_node->job) < 0) {
            //Entering this block indicates that the new job also has a lower priority than the job after the current job in the q. So we recurse.
            insert_aux(new_node, &next_node);
        } else{
            //Entering this block indicates that the new job has a greater or equal priority than the q element AFTER the current q element we're comparing against.
            //This branch is only reached if the new job has a lower priority than the current node job AND a greater priority than the next node's job.
            //As a result, we initialize a node for the job, and place it between the current node and the next node.

            new_node->next = next_node;
            (*current_node)->next = new_node;
        }
    }else{
        //Entering this block indicates that the new job has a greater priority than the current node's job.
        //As a result, we initialize a node for the job, and place it before the current node.
        new_node->next = *current_node;
        if (current_node == get_queue()){
            //If the current node is the very first node in the q, then the global q pointer needs to be updated to point to the new node.
            *get_queue() = new_node;
        }
    }
}
///Sorts the list by copying every node pointer into an array, resetting the queue, and then reinserting each node into the queue.
///This function should only be called by the Scheduler in the Scheduler thread.
void sort(){
    int length = job_queue_length();

    //Create a copy of all Node*'s. Otherwise, it will be impossible to retrieve the nodes after their pointers are cleared with clear_node_linke_length();
    Node* nodes[length];
    for (int i = 0; i < length; i ++){
        nodes[i] = get_node(i);
    }

    //Set all 'next' members of each Node to NULL, so that they can be properly reset.
    clear_node_links();

    //Insert them one by one. insert() automatically places them in the correct order.
    for (int i = 0; i < length; i ++){
        insert(nodes[i]);
    }
    //Print job queue if non empty.
    if (length > 0){
        print_job_queue();
        printf("[SCHEDULER] Queue has been reordered.\n>");
    }else{
        printf("[SCHEDULER] Scheduling Policy updated.\n");
    }
}

/// Retrieves the current policy
/// \param policy | A pointer to the string to copy the policy string to
void get_policy(char policy[]){
    if (schedule_comparator == compare_age)
        strcpy(policy, "FCFS");
    else if (schedule_comparator == compare_priority)
        strcpy(policy, "Priority");
    else if (schedule_comparator == compare_duration)
        strcpy(policy, "SJF");
}

/// Retrieves the current buffer size
/// \return | The size of the buffer
int get_buffer_size(){
    int count = 0;
    for (int i = 0; i < 100; i ++){
        if (job_buffer[i])
            count ++;
    }
    return count;
}
