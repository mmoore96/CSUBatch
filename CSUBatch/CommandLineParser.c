//
//  CommandLineParser.c
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
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
    printf(prompt, AUTHORS);    //Print welcome prompt
    while (active){
        printf(">");
        bool command_found = false; //We assume a command will not be found before checking.
        fgets(in, 255, stdin);  //Grab user input, max of 255 characters. TODO: Add input validation for the input
        for (int i = 0; i < 8; i ++){
            if (strncmp(in, string_array[i], get_string_length(in)) == 0){ //If command name matches a command

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

    if(parse_input(3, argv)){
        int time = (int)strtol(time_ptr, NULL, 0); //Convert time from string to int
        int priority = (int)strtol(priority_ptr, NULL, 0); //Convert priority from string to int
        Job* job = create_job(name_ptr, time, priority); //create job
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
