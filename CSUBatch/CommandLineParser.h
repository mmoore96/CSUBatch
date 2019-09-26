//
//  CommandLineParser.h
//  CSUBatch
//
//  Created by George Moore and Tayler Cooper on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//  Copyright © 2019 Tayler Cooper. All rights reserved.
//

#ifndef CSUBATCH_COMMANDLINEPARSER_H
#define CSUBATCH_COMMANDLINEPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Scheduler.h"


int start_ui(void);
void run(void);
void list(void);
void set_fcfs(void);
void set_sjf(void);
void set_priority(void);
void test(void);
void quit(void);
void help(void);
bool parse_input(int argc, char* argv[]);
int get_string_length(const char string[]);
int is_num(char c);
int is_alpha(char c);
int is_num_str(const char str[]);
typedef void (*command_array)();



#endif //CSUBATCH_COMMANDLINEPARSER_H
