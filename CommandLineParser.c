//
// Created by trcoo on 9/3/19.
//

#include "CommandLineParser.h"
#include "UI_Strings.h"

//The following arrays contain the command strings that execute commands, and the commands themselves, respectively.
//Because they are the same length and are ordered the same, each index provides a mapping between each string and its command.
//The run string and command are ommitted because the run function contains parameters, and can't be added to the function array.
const char* string_array[] = {list_str, fcfs_str, sjf_str, priority_str, test_str, help_str, quit_str};
command_array (commands[7]) = {list, fcfs, sjf, priority, test, help, quit};

bool active = true;


//This is the main loop of the command loop. It prints the initial prompt, initializes our input buffer,
//and begins looping, asking for input and carrying out tasks until 'quit' is entered and returns from the loop.

int start_ui(){
    printf(prompt, AUTHORS);
    char in[MAX_CHARS] = "";    //Size of 8 because the longest command a user is expected to enter is 8 characters.
    while (active){
        printf(">");
        scanf("%s", in);
        //If user enters 'run', call run() with user input
        if (strncmp(in, run_str, MAX_CHARS) == 0){
            run(in);
        }
        //Otherwise iterate over the other commands to find a matching.
        else for (int i = 0; i < 7; i ++){
            if (strncmp(in, string_array[i], MAX_CHARS) == 0){
                (*commands[i])();
            }
        }
    }
    return 0;
}

void run(char* args){

}

void  list(){

}

void fcfs(){

}

void sjf(){

}

void priority(){

}

void test(){

}

void quit(){
    active = false;
}


void help(){
    printf(info);
}

