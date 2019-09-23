#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Simple micro benchmark.
//Will wait for the amount of time specified as command line parameter in seconds
//Default time is 1 second
int main(int argc, char* argv[]){
    sleep(atoi(argv[1]));
    return 0;
}
