all: batch_job
	gcc -o CSUBatch CommandLineParser.c Dispatcher.c JobQueue.c Job.c Scheduler.c SchedulingPolicies.c main.c *.h -lpthread

batch_job:
	gcc -o ./bin/batch_job batch_job.c
