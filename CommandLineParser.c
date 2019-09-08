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
//That is, if user enters a string that matches string_array[i], then the function at command_array[i] is called.
const char* string_array[] = {run_str, list_str, fcfs_str, sjf_str, priority_str, test_str, help_str, quit_str};
command_array (commands[8]) = {run, list, set_fcfs, set_sjf, set_priority, test, help, quit};

//When this is set to false, the application exits.
bool active = true;

//Our input buffer
char in[255] = "";

//A buffer for holding error messages. When an error occurs, its description will be stored here.
//If it is not an empty string at the end of each start_ui loop, it should be printed, and then set to an empty string.
char error_log[255] = "";


//This is the main loop of the command loop. It prints the initial prompt, initializes our input buffer,
//and begins looping, asking for input and carrying out tasks until 'quit' is entered and returns from the loop.

int start_ui(){
    create_job_queue();
    char* command_name; //The first word of the user input will be interpreted as the command to be called.
    printf(prompt, AUTHORS);    //Print welcome prompt
    while (active){
        printf(">");
        bool command_found = false; //We assume a command will not be found before checking.
        fgets(in, 255, stdin);  //Grab user input, max of 255 characters. TODO: Add input validation for the input
        command_name = strtok(in, " \n"); //Grab the first word
        for (int i = 0; i < 8; i ++){
            if (strcmp(command_name, string_array[i]) == 0){ //If command name matches a command
                (*commands[i])(); //Execute command
                command_found = true;
                break; //Stop loop if command found
            }
        }
        if (command_found == false){
            strcpy(error_log, "Unknown command. Type help for command list");
        }

        //Check if error_log is not empty string
        if (error_log[0] != '\0'){
            printf("ERROR: %s", error_log); //Print error
            error_log[0] = '\0'; //Clear error
        }
        strcpy(in, "");
    }
    return 0;
}

void run(){
    //Declare pointers to hold the job name, time and priority, which will be parsed from the users input
    char name_ptr[100];
    char time_ptr[100];
    char priority_ptr[100];

    //Wrap into an array to pass into parse_input
    char *argv[3] = {name_ptr, time_ptr, priority_ptr};

    //Provide parse_input with our empty array of pointers, it will separate the arguments and put them in each of the arrays.
    if(parse_input(3, argv)){
        int time = (int)strtol(time_ptr, NULL, 0); //Convert time from string to int
        int priority = (int)strtol(priority_ptr, NULL, 0); //Convert priority from string to int
        Job* job = create_job(name_ptr, time, priority); //create job
        enqueue(job); //Add to queue
    }
}

//TODO: Check for buffer overflow event
//Prints job information
void list(){
    char string[255] = "";
    for (int i = 0; i < job_queue_length(); i ++){
        Job* job = get_job(i);
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
    free_job_queue();
    active = false;
}


void help(){
    printf(info);
}

//Split the input strings into discrete arguments using strtok
//argc is the number of arguments expected form the string. Will be 3 when used with run
//and 6 when used with test
//Returns false if an error occurred and places error message in error_log global. Returns
bool parse_input(int argc, char* argv[]){
    bool success = true;

    //Copy each whitespace separated word into each argv index
    for (int i = 0; i < argc; i ++){
        strncpy(argv[i], strtok(NULL, " "), ARGUMENT_SIZE + 1);
        if (strlen(argv[i]) > 100){
            strcpy(error_log, "ERROR: Maximum argument size 100 exceeded. Arguments must be 100 characters or fewer");
            success = false;
            break;
        }
        printf("%d\n", (signed int)strlen(argv[i]));
        if (argv[i] == NULL){
            strcpy(error_log, "ERROR: Too few arguments. Try help.");
            success = false;
            break;
        }
    }
    //If a word remains in the input string after the appropriate number of arguments have been taken, abort.
    if (strtok(NULL, " ") != NULL){
        strcpy(error_log, "ERROR: Too many arguments. Try help.");
        success = false;
    }
    return success;
}
