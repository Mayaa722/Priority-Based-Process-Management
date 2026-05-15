#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  int pid1 = fork();
  if(pid1 == 0){
    setpriority(getpid(), 5);
    printf("[A] My priority is: %d\n", getpriority(getpid()));
    for(int i = 0; i < 5; i++){
      printf("HIGH priority process running: %d\n", i);
      sleep(10);
    }
    exit(0);
  }

int pid2 = fork();
  if(pid2 == 0){
    setpriority(getpid(), 15);
    printf("[B] My priority is: %d\n", getpriority(getpid()));
    for(int i = 0; i < 5; i++){
      printf("LOW priority process running: %d\n", i);
      sleep(10);
    }
    exit(0);
  }

  wait(0);
  wait(0);
  printf("Done.\n");
  exit(0);
}
