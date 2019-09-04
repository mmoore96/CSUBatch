cmake_minimum_required(VERSION 3.14)
project(CSUBatch C)

set(CMAKE_C_STANDARD 11)

add_executable(CSUBatch main.c Scheduler.c Scheduler.h Dispatcher.c Dispatcher.h CommandLineParser.c CommandLineParser.h Job.c Job.h UI_Strings.h)