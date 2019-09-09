//
//  UI_Strings.h
//  CSUBatch
//
//  Created by Michael Moore on 9/4/19.
//  Copyright © 2019 George Moore. All rights reserved.
//

//#ifndef CSUBATCH_UI_STRINGS_H
//#define CSUBATCH_UI_STRINGS_H
//
////The following are strings which will be compared against the user input when deciding what command to execute.
////I've read that macros are more effective as basic constants than variable definitions. Feel free to correct me.
//#define run_str "run"
//#define list_str "list"
//#define fcfs_str "fcfs"
//#define sjf_str "sjf"
//#define priority_str "priority"
//#define test_str "test"
//#define help_str "help"
//#define quit_str "quit"
//
//#define AUTHORS "Tayler Cooper & George Moore"
//
////The maximum number of characters to compare against each possible command string
////is 10. This number is arbitrary, but must be larger than the longest possible command string, otherwise
////input like 'runaad' will call run() and priorityasda would run priority().
//#define MAX_CHARS 10
//
//#define prompt "Welcome to %s's batch job scheduler Version 0.0\n \
//                Type 'help' to find more about CSUbatch commands.\n"
//
//
//#define info "run <job> <time> <pri>: submit a job named <job>,\n \
//\texecution time is <time>,\n \
//\tpriority is <pri>.\n \
//list: display the job status.\n \
//change the scheduling policy to FCFS.\n \
//sjf: change the scheduling policy to SJF.\n \
//priority: change the scheduling policy to priority.\n \
//test: <benchmark> <policy> <num_of_jobs> <priority_levels>\n \
//\t <min_CPU_time> <max_CPU_time>\n \
//quit: exit CSUbatch\n"
//
//#endif //CSUBATCH_UI_STRINGS_H
