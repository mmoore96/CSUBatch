//
//  CommandLineParser.h
//  CSUBatch
//
//  Created by Michael Moore on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//
#ifndef CSUBATCH_COMMANDLINEPARSER_H
#define CSUBATCH_COMMANDLINEPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int start_ui();
void run(char*);
void list();
void fcfs();
void sjf();
void priority();
void test();
void quit();
void help();
typedef void (*command_array)();


#endif //CSUBATCH_COMMANDLINEPARSER_H
