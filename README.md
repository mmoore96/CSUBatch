# CSUBatch - A Pthread-based Batch Scheduling System
Batch System for queueing and executing jobs based on different scheduling polices in C.

1. Project Overview	
The goal of this project is to design and implement a batch scheduling system called  CSUbatch using the C programming language and the Pthread library. CSUbatch is comprised of two distinctive and collaborating threads, namely, the scheduling thread and the dispatching thread. The scheduling thread enforces scheduling policies, whereas the dispatching thread has submitted jobs executed by the execv() function. The two threads are created by the pthread_create () function (see also [2] for an example).

The synchronization of these two threads must be implemented by condition variables. To address the synchronization issues in CSUbatch, you may envision the scheduling and dispatching modules as a producer and a consumer, respectively. In addition to condition variables, mutex must be adopted to solve the critical section problem in CSUbatch.

The three scheduling policies to be implemented in your CSUbatch are FCFS (a.k.a., First Come, First Served), SJF (a.k.a., Shortest Job First), and Priority (a.k.a., Priority-based scheduling). Please refer to [3] for details on these three scheduling algorithms.

After implementing three scheduling policies (i.e., FCFS, SJF, and priority based), you are required to compare the performance of these three scheduling policies under various workload conditions. 


2. CSUbatch: A Batch Scheduling System
2.1 System Architecture
Fig. 1 depicts the system architecture of the CSUbatch scheduling system, which consists of a scheduling module and a dispatching module. The scheduling module is in charge of the following two tasks: 
(1) accepting submitted jobs from users and 
(2) enforcing a chosen scheduling policy. 

The dispatching module have two responsibilities listed below: 
(1) making use of the execv()function to run jobs sorted in the job queue and 
(2) measuring the execution time and response time (a.k.a., turn-around time) of each finished job.








Fig. 1 The system architecture of the CSUbatch scheduler

2.2 System Design
A data flow diagram or DFD illustrates how data is processed by your CSUbatch system in terms of inputs and outputs. In this project, you will be required to draft a data flow diagram for your CSUbatch system. Fig. 1 outlined in Section 2.1 should be an inspiration when you design the data flow diagram, which is a driving force behind the design of CSUbatch’s important data structures and function prototypes.

Please keep in mind that during the system design phase, you shouldn’t be concerned with the implementation details like how to use the execv() function and how to apply the pthread library. You should be capable of crafting a simple yet elegant system design without prior knowledge of Pthread and multithreaded programming.

Please refer to [4] for commonly used data flow diagrams symbols. A few sample data flow diagrams also can be found in [4].

2.3 Two Optional Modules for Job Submissions and Performance Measurements
It is worth noting that if the job submission portion in the scheduling module becomes complicated, it is prudent to separate job submission from the scheduling module. Thus, you should create another module called the job submission module. 

Similarly, in case the performance measuring part of the dispatching module is non-trivial, it is a wise decision to implement a dedicated module for performance measurement and comparison.

2.4 Critical Sections and Synchronizations
The scheduling module and the dispatching module are launched as two concurrent threads created by the pthread_create () function (see also [2] for an example). The two threads share a job queue, meaning that you must incorporate the mutex mechanism in CSUbatch to protect the shared job queue residing in critical sections. You may identify a few shared variables other than the job queue, please apply mutex available in the PThread library to implement all the critical sections.

Apart  from critical sections, the synchronization between the scheduling module and the dispatching module should be addressed using condition variables, the functions of which are available in the PThread library [1]. 

The synchronization design pattern of CSUbatch is the conventional producer-consumer problem [5]. To tackle the synchronization problem in CSUbatch, you may simple treat the scheduling module as a producer and the dispatching modules as a consumer. More specifically, the scheduling module issues (i.e., produces) newly submitted jobs into the job queue, enforcing a scheduling policy; the dispatching module extracts (i.e., consumes) a job from the job queue to run the job. 

 Important!  You are required to take the full advantage of the PThread library to make use of condition variables and mutexes to solve the aforementioned critical section and synchronization problems in CSUbatch. Please refer to [1] for the detailed information on the PThread library. A list of important PThread functions to be employed in this project is given below.
•	pthread_create (thread,attr,start_routine,arg)
The mutex functions:
•	pthread_mutex_lock (mutex) 
•	pthread_mutex_unlock (mutex)

The condition-variable functions:
•	pthread_cond_init (condition,attr)
•	pthread_cond_wait (condition,mutex) 
•	pthread_cond_signal (condition)

 Sample Code  In this project-specification package, you may find an example (see condvar.c) of using condition variables. This example source code demonstrates the use of a few commonly used Pthread condition variable functions. In condvar.c, the main function creates three threads, two of which perform work and update a "count" variable. The third thread waits until the count variable reaches a specified value.

2.5 Three Scheduling Policies/Algorithms
In this project, you must implement three scheduling policies in CSUbatch. Throughout this specification document, we use terms policies and algorithms interchangeably. The three algorithms to be investigated in the project are:
•	FCFS: First Come, First Served, 
•	SJF: Shortest Job First, and 
•	Priority: Priority-based scheduling. 

 Important!  You may refer to [3] for the detailed descriptions on these three scheduling algorithms. The three algorithms should be implemented in the scheduling module of CSUbatch (see also Fig. 1 in Section 2.1).

3. Performance Evaluation
3.1 Performance Metrics 
After implementing the three scheduling policies (i.e., FCFS, SJF, and Priority), you will be in a position to compare the performance of these algorithms under various workload conditions (see also Section 2.6). The first step toward evaluating and comparing the performance of the three scheduling algorithms is to design performance metrics (see the list below) and workload conditions (see Section 2.6). Performance metrics measure your CSUbatch’s behaviors and performance. The two suggested performance metrics are:
•	Average Response Time
•	Throughput

You may also consider the following optional performance metrics:
•	Maximum Response Time
•	Minimum Response Time
•	Response Time Standard Deviation


3.2 Micro Batch-Job Benchmarks
After the scheduling module makes scheduling decisions, the dispatching module launches a job from the head of the job queue with the execv() function. Jobs submitted to the scheduling module can be batch jobs, which may be either large batch-job benchmarks or micro batchmarks. You are suggested to implement a micro batch-job benchmark, which takes running-time as an input parameter. For example, let’s consider a micro benchmark called “batch_job”,  the format of which is “batch_job <exe_time>”. You may run batch_job from the Linux terminal as, 
	$./batch_job 5
This micro benchmark will run for approximately 5 seconds. 

 Important!  Your dispatching module should be capable of launching your micro benchmarks. Because your micro benchmarks are in the batch mode, there shouldn’t be any output displayed in the Linux terminal. In case your benchmarks must output any data, the data should be saved in output files. 

3.3 Workload Conditions
We model a workload condition using three parameters, namely, the number of submitted jobs, arrival rate, and load distribution. 
•	The number of submitted jobs: the number of job submitted in each experiment.
•	Arrival rate: the number of job submitted per time unit (e.g., 1 second). 
•	Load Distribution: distribution of batch jobs’ execution times. 

The sample workload-condition setup is summarized in the following table. You may use any setup to conduct your experiments. 

Workload Parameters	Default Values
Number of Submitted Jobs	5, 10, 15, 20, 25
Arrival Rate	0.1, 0.2, 0.5, 1.0 No./Second
Load Distribution (Uniform)	[0.1, 0.5], [0.1, 1], [0.5, 1], [1, 10]

The load distribution can be either uniform or normal distribution. The implementation of the uniform distribution is, of course, easier than that of the normal distribution.

3.4 Automated Performance Evaluation
 Important!  It is impractical to evaluate performance using CSUbatch’s command line. Please propose a way of automatically evaluating performance of the three scheduling algorithms. You are suggested to implement a performance evaluation module, where all the designed workload conditions are implemented through hard coding.

4. User Interface
The commonly used commands in CSUbatch are (1) help, (2) run, (3) list, and (4) change scheduling policies. In what follows, we show the sample dialog for each command.

 Important!  Your program's output should match the style of the sample output. You will lose points if you don’t follow the user interface specified in this Section. 

4.1 Help Information
The name of your batch-job scheduler is CSUbatch, which takes no input parameter. Here is a sample dialog (where the user input is depicted as Bold, but you do not need to display user input in bold.). In the sample usage below, please replace “Dr. Zhou” with your name. 
