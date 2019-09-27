#include <stdlib.h>
#include <unistd.h>

void main(int argc, char* argv[]){
  sleep(strtol(argv[1], NULL, 10));
}
