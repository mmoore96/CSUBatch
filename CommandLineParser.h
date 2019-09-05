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
void fcfs();
void sjf();
void priority();
void test();
void quit();
void help();
typedef void (*command_array)();


#endif //CSUBATCH_COMMANDLINEPARSER_H
