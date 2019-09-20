//
// Created by trcoo on 9/3/19.
//

#ifndef CSUBATCH_COMMANDLINEPARSER_H
#define CSUBATCH_COMMANDLINEPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Scheduler.h"
#include "Errors.h"


int start_ui();
void run();
void list();
void set_fcfs();
void set_sjf();
void set_priority();
void test();
void quit();
void help();
bool parse_input(int argc, char* argv[]);
int get_string_length(const char string[]);
int is_num(char c);
int is_alpha(char c);
typedef void (*command_array)();



#endif //CSUBATCH_COMMANDLINEPARSER_H
