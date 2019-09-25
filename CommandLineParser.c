//
//  CommandLineParser.c
//  CSUBatch
//
//  Created by Tayler Cooper and George Moore
//

#include "CommandLineParser.h"
#include "Scheduler.h"
#include "Job.h"
#include "JobQueue.h"
#include "Analytics.h"
#include <stdlib.h>
#include <string.h>

//The following arrays contain the command strings that execute commands, and the commands themselves, respectively.
//Because they are the same length and are ordered the same, each index provides a mapping between each string and its command.
//That is, if user enters a string that matches string_array[i], then the function at command_array[i] is called.
char* string_array[] = {run_str, list_str, fcfs_str, sjf_str, priority_str, test_str, help_str, quit_str};
command_array (commands[8]) = {run, list, set_fcfs, set_sjf, set_priority, test, help, quit};

//The Scheduling and Dispatching threads constantly check this global, terminating when it becomes false.
bool active = true;

//Our input buffer
char in[255] = "";


//This is the main loop of the command loop. It prints the initial prompt, initializes our input buffer,
//and begins looping, asking for input and carrying out tasks until 'quit' is entered and returns from the loop.

int start_ui(){
    printf(prompt, AUTHORS);    //Print welcome prompt
    while (active){
        printf(">");
        bool command_found = false; //We assume a command will not be found before checking.
        fgets(in, 255, stdin);  //Grab user input, max of 255 characters.
        for (int i = 0; i < 8; i ++){
            char* command_name = string_array[i];

            if (strncmp(in, command_name, get_string_length(command_name)) == 0){ //If command name matches a command

                (*commands[i])(); //Execute command
                command_found = true;
                break; //Stop loop if command found
            }
        }
        if (command_found == false){
            printf("Unknown command. Type help for command list");
        }

    }
    return 0;
}

void run(){
    //Declare pointers to hold the job name, time and priority, which will be parsed from the users input
    char name_ptr[100];
    memset((void*)name_ptr, 0, 100);
    char time_ptr[100];
    memset((void*)time_ptr, 0, 100);
    char priority_ptr[100];
    memset(priority_ptr, 0, 100);
    //Wrap into an array to pass into parse_input
    char *argv[3] = {name_ptr, time_ptr, priority_ptr};

    if(parse_input(3, argv)){
        int job_time = (int)strtol(time_ptr, NULL, 0); //Convert time from string to int
        int priority = (int)strtol(priority_ptr, NULL, 0); //Convert priority from string to int
        Job* job = create_job(name_ptr, job_time, priority); //create job

        printf("%s has been submitted.\n", argv[0]);
        printf("Total number of jobs waiting for dispatch: %d\n", job_queue_length() + 1); //a + 1 to include the job being added.
        printf("Jobs currently running: %d\n", current_job != NULL);
        printf("Expected waiting time: %d\n", job_queue_time() + job_time); // Add the time of the jobs in the queue, the remaining time of the running job, and the new job.
        //The actual function call to place the job in the queue is after the previous print statements
        //because there's no guarantee that the Scheduler will be able to obtain a lock and place the
        //job in the queue before the print statements calculate their values.
        total_number_of_jobs++;
        post(job); //Post to scheduler
    }

}

//Prints job information
void list(){
    print_job_queue();
}

void set_fcfs(){
    set_scheduling(0);
}

void set_sjf(){
    set_scheduling(1);
}

void set_priority(){
    set_scheduling(2);
}

void test(){
    //Declare parameters
    char benchmark_ptr[100]; //Size of 100 is arbitrary
    char policy_ptr[100]; //Size of largest policy, FCFS, is 4.
    char job_num_ptr[100]; //Size of 100 is arbitrary
    char priority_levels[100]; //Size of 100 is arbitrary
    char min_cpu_time_ptr[100]; //Size of 100 in arbitrary
    char max_cpu_time_ptr[100]; //Size of 100 is arbitrary

    char *argv[6] = {benchmark_ptr, policy_ptr, job_num_ptr, priority_levels, min_cpu_time_ptr, max_cpu_time_ptr};
    for (int i = 0; i < 6; i ++){
        memset((void*)argv[i], 0, 100);
    }

}

void quit(){
    //Free up all job memory
    active = false;
    free_job_queue();
    if (total_number_of_jobs > 0){
        float n_jobs = (float)total_number_of_jobs; //Cast to float for division below.
        float avg_CPU_time = CPU_time / n_jobs;
        float avg_waiting_time = waiting_time / n_jobs;
        printf("Total number of jobs submitted: %d\n", (int)n_jobs);
        printf("Average turnaround time: %.2f\n", avg_CPU_time + avg_waiting_time);
        printf("Average CPU time: %.2f\n", avg_CPU_time);
        printf("Average waiting time: %.2f\n", avg_waiting_time);
        printf("Throughput: %.2f No./second\n", n_jobs / (float)(time(NULL) - starting_time));
    }else
        printf("As no jobs were ever provided, there are no analytics.\n");

}


void help(){
    printf(info);
}

//Split the input strings into discrete arguments using strtok
//argc is the number of arguments expected form the string. Will be 3 when used with run
//and 6 when used with test.c
//Returns false if an error occurred and places error message in error_log global. Returns
bool parse_input(int argc, char* argv[]){
    int word_size = -1;
    char* word_beginning = malloc(255);
    memset(word_beginning,0,255);
    strncpy(word_beginning, in + 4, 251);
    char* word_end = word_beginning;

    for ( int i = 0; i < argc + 1; i ++){
        //For each word in input string
        if (is_num(word_beginning[0]) || is_alpha(word_beginning[0])){
            //Entered if starting character is numeric or alphabetical
            if (i == argc){
                printf("ERROR: Too many arguments. Try help.\n");
                return false;
            }
            for( int j = 0; j < 255; j++) {
                //For each character in word
                if (*(word_beginning + j) == ' ' || *(word_beginning + j) == '\n') {
                    //Entered if we reach a space or newline after the end of a word
                    word_end = word_beginning + j - 1;
                    word_size = j;
                    break;
                }
            }
        }else{
            if(i < argc){
                printf("ERROR: Too few arguments. Try help.\n");
                return false;
            }else{
                break;
            }
        }

        if( i < argc ){
            strncpy(argv[i], word_beginning, word_size); //Copy the range of the word to the arguments pointer
            word_beginning = word_end + 2; //Update the pointer to the beginning of the next word.
        }
    }
    for (int i = 1; i < argc; i ++){
        if (!is_num_str(argv[i])){
            printf("ERROR: Argument %d must be integer.\n", i);
            free(word_beginning);
            return false;
        }

    }
    return true;
}

int get_string_length(const char string[]){
    //If the ascii of the first character in string is less than a or more than z, it is not a valid command.
    if ((int)string[0] < (int)'a' || (int)string[0] > (int)'z'){
        return 0;
    }else{
        return 1 + get_string_length(string + 1);
    }
}

int is_num(char c){
    int char_code = (int)c;
    if (char_code >= 48 && char_code <= 57){
        return 1;
    }else{
        return 0;
    }
}

int is_alpha(char c){
    int char_code = (int)c;
    if (char_code >= 97 && char_code <= 122){
        return 1;
    }else{
        return 0;
    }
}

// Returns 1 if the string is a number
int is_num_str(const char str[]){
    for (int i = 0; str[i]; i ++){
        if (!is_num(str[i]))
            return 0;
    }
    return 1;
}
