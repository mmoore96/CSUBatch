//
//  CommandLineParser.c
//  CSUBatch
//
//  Created by Michael Moore on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
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
    memset((void*)name_ptr, 0, 100);
    char time_ptr[100];
    memset((void*)time_ptr, 0, 100);
    char priority_ptr[100];
    memset(priority_ptr, 0, 100);

    //Wrap into an array to pass into parse_input
    char *argv[3] = {name_ptr, time_ptr, priority_ptr};

    //Provide parse_input with our empty array of pointers, it will separate the arguments and put them in each of the arrays.

    //strcpy(in, in[4:255]);

    if(parse_input(3, argv)){
//        printf("name: %s\n", argv[0]);
//        printf("Duration: %s\n", argv[1]);
//        printf("priority: %s\n", argv[2]);
        int time = (int)strtol(time_ptr, NULL, 0); //Convert time from string to int
        int priority = (int)strtol(priority_ptr, NULL, 0); //Convert priority from string to int
        Job* job = create_job(name_ptr, time, priority); //create job
        post(job); //Post to scheduler
    }
}

//TODO: Check for buffer overflow event
//Prints job information
void list(){
    print_job_queue();
}

void set_fcfs(){
    set_fcfs_scheduling();
}

void set_sjf(){
    set_sjf_scheduling();
}

void set_priority(){
    set_priority_scheduling();
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
    int endj = 0;
    int q = 0;
    bool success = true;
    char* beginning = malloc(255);
    memset(beginning,0,255);
    strncpy(beginning, in + 4, 251);
    char* end = beginning;
    
    for ( int i = 0; i < argc + 1; i ++){
        if(beginning[0] == ' ' || beginning[0] == '\0'){
        
            if(i <= 2){
                //When we have too many arguments (This works)
                printf("ERROR: Too few arguments. Try help.\n");
                return success == false;
            }else{
                break;
            }
            
            
        }else{
            
            for( int j = 0; j < 255; j++){
                if(*(beginning + j) != ' ' && *(beginning + j) != '\n'){ //Triggers when word is found
                    //In testing this never gets called EVER!
                    //TODO: Figure out if this is even needed at all
                    if (i == argc + 1){
                        printf("BAD!\n");
                    }
                    }else{
                    
                        end = beginning + j - 1;
                        endj = j;
                        break;
                        }
            
            }
            //&& beginning[0] != ' '
            //^left over code that might be used^
            //TODO: Need to tell user that they have entered in too many arguments (This does not work).
            //This was implemented below.
            //TODO: Remove after further testing of else statement below.
            if( i == argc + 1 ){
                printf("ERROR: Too many arguments. Try help\n");
                success = false;
                break;
            }
            
            
            if( q < 3 ){
            strncpy(argv[i], beginning, endj);
            beginning = end + 2;
            q++;
            //TODO: This print statement will be removed once testing is over
            printf("Beginning pointer %p\n", beginning);
                
            }else{
                //Prints message when we have too many arguments (This works).
                printf("You have entered in an extraneous argument (which could be a space), this was disregarded.\n");
            }
        }}
    return success;
}
            
