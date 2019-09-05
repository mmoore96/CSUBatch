//
// Created by trcoo on 9/3/19.
//

#include "CommandLineParser.h"
#include "UI_Strings.h"

//The following arrays contain the command strings that execute commands, and the commands themselves, respectively.
//Because they are the same length and are ordered the same, each index provides a mapping between each string and its command.
//The run string and command are ommitted because the run function contains parameters, and can't be added to the function array.
const char* string_array[] = {run_str, list_str, fcfs_str, sjf_str, priority_str, test_str, help_str, quit_str};
command_array (commands[8]) = {run, list, fcfs, sjf, priority, test, help, quit};

bool active = true;
char in[MAX_CHARS] = "";


//This is the main loop of the command loop. It prints the initial prompt, initializes our input buffer,
//and begins looping, asking for input and carrying out tasks until 'quit' is entered and returns from the loop.

int start_ui(){
    printf(prompt, AUTHORS);
    while (active){
        printf(">");
        bool command_found = false;
        scanf("%s", in);
        for (int i = 0; i < 8; i ++){
            if (strncmp(in, string_array[i], MAX_CHARS) == 0){
                (*commands[i])();
                command_found = true;
                break;
            }
        }
        if (command_found == false){
            printf("Unknown command. Type help for command list");
        }

    }
    return 0;
}

void run(){

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

