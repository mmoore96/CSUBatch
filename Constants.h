//
// Created by trcoo on 9/4/19.
// The following is a database of strings used in the CommandLineParser.
// I've put them in a dedicated file for modularity
//

#ifndef CSUBATCH_CONSTANTS_H
#define CSUBATCH_CONSTANTS_H

//The following are strings which will be compared against the user input when deciding what command to execute.
//I've read that macros are more effective as basic constants than variable definitions. Feel free to correct me.
#define run_str "run"
#define list_str "list"
#define fcfs_str "fcfs"
#define sjf_str "sjf"
#define priority_str "priority"
#define test_str "test"
#define help_str "help"
#define quit_str "quit"

//This macro defines the maximum character length of each user argument.
#define ARGUMENT_SIZE 25

#define AUTHORS "Tayler Cooper & George Moore"

#define prompt "Welcome to %s's batch job scheduler Version 1.0\n \
                Type 'help' to find more about CSUbatch commands.\n"


#define run_help "run <job> <time> <pri>: \n\tSubmits a job named <job>, \
execution time is <time>, \
priority is <pri>.\n"

#define list_help "list: display the job status.\n"

#define fcfs_help "Change the scheduling policy to FCFS.\n"

#define sjf_help "sjf: change the scheduling policy to SJF.\n"

#define priority_help "priority: change the scheduling policy to priority.\n"

#define test_help "test: <benchmark> <policy> <num_of_jobs> <priority_levels> \
<min_CPU_time> <max_CPU_time>\n\t Submits a batch of <num_of_jobs> jobs named <benchmark>\
 with random priority levels between 0 and <priority_levels> and execution times randomly\
between <min_CPU_time> and <max_CPU_time using scheduling policy <policy>\n"

#define quit_help "quit: exit CSUbatch\n"


#endif //CSUBATCH_CONSTANTS_H
