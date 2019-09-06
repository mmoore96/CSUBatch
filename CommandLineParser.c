//
// Created by trcoo on 9/3/19.
//

#include "CommandLineParser.h"
#include "UI_Strings.h"
#include "Scheduler.h"
#include "Job.h"
#include "JobQueue.h"
#include <stdlib.h>
#include <string.h>

//The following arrays contain the command strings that execute commands, and the commands themselves, respectively.
//Because they are the same length and are ordered the same, each index provides a mapping between each string and its command.
//The run string and command are ommitted because the run function contains parameters, and can't be added to the function array.
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
    char* first_command;
    printf(prompt, AUTHORS);
    while (active){
        printf(">");
        bool command_found = false;
        fgets(in, 255, stdin);
        first_command = strtok(in, " ");
        for (int i = 0; i < 8; i ++){
            if (strcmp(in, string_array[i]) == 0){
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
    //char buffer[256];
    //memset(buffer, 0, 256);
    //strncpy(buffer, in, 256);
    //strcpy(in, buffer);
    char *_argv[3];
    Job* job = malloc(sizeof(Job));
    printf("JOB POINTER %ld ALLOCATED", (long)job);
    char **argv = parse_input(3, _argv);
    job->name = argv[0];
    job->job_time = strtol(argv[1], NULL, 0);
    job->priority = strtol(argv[2], NULL, 0);
    //TODO: BELOW IS THE CODE FOR FREEING MEMORY ALLOCATED IN PARSE_INPUT FOR STORING THE ARGUMENTS; THIS SHOULD BE REFACTORED INTO A SEPARATE FUNCTION OR SOMETHING
    //TODO: OR REFACTOR PARSE_INPUT TO AVOID ALLOCATING MEMORY
    for (int i = 0; i < 3; i ++){
        free(_argv[i]);
    }
    //TODO: GIVE JOB TO SCHEDULER; REFACTOR THE CODE BELOW
    push(&q, job);

}

void  list(){
    for (int i = 0; i < q.length; i ++){
        Job* job = get_job(&q, i);
        printf("Name: %s, Time: %d, Priority Enum: %d", job->name, job->job_time, job->priority);
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
char** parse_input(int argc, char* argv[]){
    bool error = false;
    //TODO: Ensure that allocating an array like below at runtime is safe, otherwise hardcode it to 6, since that's the max number of arguments for any command (only test command takes 6 args)
    //char* argv[argc];// = malloc(argc * sizeof(char*));
    for (int i = 0; i < argc; i ++){
        argv[i]= (char*)malloc(26);  //TODO: SOFTCODE OR BETTER HANDLE THE MAX SPACE FOR EACH ARGUMENT. THIS IS A TEMPORARY SOLUTION

    }
    //argv[0] = strtok(in, " ");
    for (int i = 0; i < argc; i ++){
        argv[i] = strtok(NULL, " ");
        if (argv[i] == NULL){
            printf("ERROR: Too few arguments. Use help");
            error = true;
            break;

        }
    }
    if (strtok(NULL, " ") != NULL){
        printf("ERROR: Too many arguments. Use help");
        error = true;
    }
    if (error){
        argv = NULL;
    }
    return argv;
}
