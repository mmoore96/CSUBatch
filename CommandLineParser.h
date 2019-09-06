//
// Created by trcoo on 9/3/19.
//

#ifndef CSUBATCH_COMMANDLINEPARSER_H
#define CSUBATCH_COMMANDLINEPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int start_ui();
void run();
void list();
void set_fcfs();
void set_sjf();
void set_priority();
void test();
void quit();
void help();
char** parse_input(int argc);
void** parse_input2(int argc, void* argv[]);
typedef void (*command_array)();



#endif //CSUBATCH_COMMANDLINEPARSER_H
