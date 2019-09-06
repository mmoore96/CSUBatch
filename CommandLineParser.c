//
// Created by trcoo on 9/3/19.
//

#include "CommandLineParser.h"
#include "Scheduler.h"
#include "Job.h"
#include "JobQueue.h"
#include <stdlib.h>
#include <string.h>

//The following arrays contain the command strings that execute commands, and the commands themselves, respectively.
//Because they are the same length and are ordered the same, each index provides a mapping between each string and its command.
const char* string_array[] = {run_str, list_str, fcfs_str, sjf_str, priority_str, test_str, help_str, quit_str};
command_array (commands[8]) = {run, list, set_fcfs, set_sjf, set_priority, test, help, quit};

bool active = true;
char in[255] = "";
//TODO: Remove this line below when necessary
JobQueue q;  //A temporary space to store jobs and debug them until the scheduler is set up. After which, jobs will be
// Given directly to to the scheduler.



//This is the main loop of the command loop. It prints the initial prompt, initializes our input buffer,
//and begins looping, asking for input and carrying out tasks until 'quit' is entered and returns from the loop.

int start_ui(){
    q.first = NULL; //Debugging
    char* command_name;
    printf(prompt, AUTHORS);
    while (active){
        printf(">");
        bool command_found = false;
        fgets(in, 255, stdin);
        command_name = strtok(in, " \n");
        for (int i = 0; i < 8; i ++){
            if (strcmp(command_name, string_array[i]) == 0){
                (*commands[i])();
                command_found = true;
                break;
            }
        }
        if (command_found == false){
            printf("Unknown command. Type help for command list\n");
        }

    }
    return 0;
}

void run(){
    char name[25];
    char time[25];
    char priority[25];

    int time1 = (int)strtol(time, NULL, 0);
    int priority1 = (int)strtol(priority, NULL, 0);

    void *argv[3] = {name, time, priority};
    parse_input2(3, argv);
    //char **argv = parse_input(3); //Parse input into array of arguments

    //name = argv[0];   //Extract name
    //time = (int)strtol(argv[1], NULL, 0); //Extract job time
    //priority = (int)strtol(argv[2], NULL, 0); //Extract priority

    Job* job = create_job(name, time1, priority1); //create job

    //TODO: BELOW IS THE CODE FOR FREEING MEMORY ALLOCATED IN PARSE_INPUT FOR STORING THE ARGUMENTS; THIS SHOULD BE REFACTORED INTO A SEPARATE FUNCTION OR SOMETHING
    //TODO: OR REFACTOR PARSE_INPUT TO AVOID ALLOCATING MEMORY
    //for (int i = 0; i < 3; i ++){
      //  printf("Freeing pointer %p\n", (void*)argv[i]);
        //free(argv[i]);
    //}
    //TODO: GIVE JOB TO SCHEDULER; REFACTOR THE CODE BELOW WHEN SCHEDULER MODULE AVAILABLE
    push(&q, job);

}

void  list(){
    char string[255] = "";
    for (int i = 0; i < q.length; i ++){
        Job* job = get_job(&q, i);
        job_string(job, string);
        printf("Job number %d\n\t %s\n", i, string);
    }
}

void set_fcfs(){

}

void set_sjf(){

}

void set_priority(){

}

void test(){

}

void quit(){
    //Free up all job memory
    free_jobs(&q);
    active = false;
}


void help(){
    printf(info);
}

//Split the input strings into discrete arguments using strtok
//argc is the number of arguments expected form the string. Will be 3 when used with run
//and 6 when used with test
//TODO: This function needs to be double checked for memory leaks and input validation
char** parse_input(int argc){
    bool error = false;
    //TODO: Ensure that allocating an array like below at runtime is safe, otherwise hardcode it to 6, since that's the max number of arguments for any command (only test command takes 6 args)

    char **argv = malloc(argc * sizeof(char*));
    if (!argv){
        printf("WARNING: null array\n");
    }
    for (int i = 0; i < argc; i ++){
        argv[i]= malloc(ARGUMENT_SIZE + 1);  //TODO: SOFTCODE OR BETTER HANDLE THE MAX SPACE FOR EACH ARGUMENT. THIS IS A TEMPORARY SOLUTION
        if (!argv[i]){
            printf("WARNING: null pointer\n");
            free(argv);
        }
        printf("Pointer %p allocated\n", (void*)argv[i]);

    }
    for (int i = 0; i < argc; i ++){
        strncpy(argv[i], strtok(NULL, " "), ARGUMENT_SIZE + 1);
        if (argv[i] == NULL){
            printf("ERROR: Too few arguments. Use help\n");
            error = true;
            break;

        }
    }
    if (strtok(NULL, " ") != NULL){
        printf("ERROR: Too many arguments. Use help\n");
        error = true;
    }
    if (error){
        argv = NULL;
    }
    return argv;
}

void** parse_input2(int argc, void* argv[]){
    bool error = false;
    //TODO: Ensure that allocating an array like below at runtime is safe, otherwise hardcode it to 6, since that's the max number of arguments for any command (only test command takes 6 args)

    if (!argv){
        printf("WARNING: null array\n");
    }
    for (int i = 0; i < argc; i ++){
        strncpy(argv[i], strtok(NULL, " "), ARGUMENT_SIZE + 1);
        if (argv[i] == NULL){
            printf("ERROR: Too few arguments. Use help\n");
            error = true;
            break;

        }
    }
    if (strtok(NULL, " ") != NULL){
        printf("ERROR: Too many arguments. Use help\n");
        error = true;
    }
    if (error){
        argv = NULL;
    }
    return argv;
}
