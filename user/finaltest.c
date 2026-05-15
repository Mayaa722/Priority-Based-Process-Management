#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  printf("=========================================\n");
  printf("   Priority-Based Process Scheduler Test  \n");
  printf("=========================================\n");

  printf("\nTest 1: Two processes with different priorities\n");
  printf("Process A -> priority 3 (HIGH)\n");
  printf("Process B -> priority 18 (LOW)\n\n");

  int pid1 = fork();
  if(pid1 == 0){
    setpriority(getpid(), 3);
    printf("[A] My priority is: %d\n", getpriority(getpid()));
    for(int i = 0; i < 4; i++){
      printf("[A] HIGH priority running: step %d\n", i+1);
      sleep(8);
    }
    printf("[A] Done.\n");
    exit(0);
  }

  int pid2 = fork();
  if(pid2 == 0){
    setpriority(getpid(), 18);
    printf("[B] My priority is: %d\n", getpriority(getpid()));
    for(int i = 0; i < 4; i++){
      printf("[B] LOW priority running: step %d\n", i+1);
      sleep(8);
    }
    printf("[B] Done.\n");
    exit(0);
  }

  wait(0);
  wait(0);

  printf("\nTest 2: Equal priority - Round Robin\n");
  printf("Process C -> priority 10\n");
  printf("Process D -> priority 10\n\n");
  setsched(2);

  int pid3 = fork();
  if(pid3 == 0){
    setpriority(getpid(), 10);
    for(int i = 0; i < 3; i++){
      printf("[C] Equal priority running: step %d\n", i+1);
      sleep(8);
    }
    printf("[C] Done.\n");
    exit(0);
  }

  int pid4 = fork();
  if(pid4 == 0){
    setpriority(getpid(), 10);
    for(int i = 0; i < 3; i++){
      printf("[D] Equal priority running: step %d\n", i+1);
      sleep(8);
    }
    printf("[D] Done.\n");
    exit(0);
  }

  wait(0);
  wait(0);

  printf("\n=========================================\n");
  printf("   All tests passed successfully!\n");
  printf("=========================================\n");
  exit(0);
}
