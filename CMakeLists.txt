cmake_minimum_required(VERSION 3.14)
project(CSUBatch C)

set(CMAKE_C_STANDARD 11)

add_executable(CSUBatch main.c Scheduler.c Scheduler.h Dispatcher.c Dispatcher.h CommandLineParser.c CommandLineParser.h Job.c Job.h Constants.h JobQueue.c JobQueue.h main.h Errors.h SchedulingPolicies.c SchedulingPolicies.h)
add_compile_options(-lpthread)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CSUBatch Threads::Threads)