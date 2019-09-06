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

#define prompt "Welcome to %s's batch job scheduler Version 0.0\n \
                Type 'help' to find more about CSUbatch commands.\n"


#define info "run <job> <time> <pri>: submit a job named <job>,\n \
\texecution time is <time>,\n \
\tpriority is <pri>.\n \
list: display the job status.\n \
change the scheduling policy to FCFS.\n \
sjf: change the scheduling policy to SJF.\n \
priority: change the scheduling policy to priority.\n \
test: <benchmark> <policy> <num_of_jobs> <priority_levels>\n \
\t <min_CPU_time> <max_CPU_time>\n \
quit: exit CSUbatch\n"

#endif //CSUBATCH_CONSTANTS_H
