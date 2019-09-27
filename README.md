# CSUBatch
Batch System for queueing and executing jobs based on different scheduling polices in C.
The main binary, CSUBatch, is in the bin folder. 
To compile from source, just use 'make' inside the root directory. The newly compiled CSUBatch binary will at the same place at bin/CSUBatch.
The target platform is Linux with GCC.

Jobs can be submitted with the syntax 'run <jobname> <job duration> <job priority>' and the application can be ended with 'quit'
A detailed listing of all commands is available by using 'help' form inside the application.
