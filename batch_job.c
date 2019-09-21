#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Simple micro benchmark.
//Will wait for the amount of time specified as command line parameter in seconds
//Default time is 1 second
int main(int argc, char* argv[]){
	if (argc == 2){
	    int t = atoi(argv[1]);
		sleep(t);
	}else{
		sleep(1);
	}
	return 0;
}
