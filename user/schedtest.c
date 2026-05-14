#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  printf("=== Scheduler Mode Test ===\n");

  // Mode 3: Aging (default)
  printf("\n-- Mode 3: Priority with Aging --\n");
  setsched(3);

  int pid1 = fork();
  if(pid1 == 0){
    setpriority(5);
    printf("HIGH (priority %d) running\n", getpriority());
    for(int i = 0; i < 3; i++){
      printf("HIGH: %d\n", i);
      sleep(5);
    }
    exit(0);
  }

  int pid2 = fork();
  if(pid2 == 0){
    setpriority(15);
    printf("LOW (priority %d) running\n", getpriority());
    for(int i = 0; i < 3; i++){
      printf("LOW: %d\n", i);
      sleep(5);
    }
    exit(0);
  }

  wait(0);
  wait(0);

  // Mode 2: Round-robin
  printf("\n-- Mode 2: Round Robin --\n");
  setsched(2);

  int pid3 = fork();
  if(pid3 == 0){
    setpriority(5);
    for(int i = 0; i < 3; i++){
      printf("P1 (prio 5): %d\n", i);
      sleep(5);
    }
    exit(0);
  }

  int pid4 = fork();
  if(pid4 == 0){
    setpriority(5);
    for(int i = 0; i < 3; i++){
      printf("P2 (prio 5): %d\n", i);
      sleep(5);
    }
    exit(0);
  }

  wait(0);
  wait(0);

  printf("\nDone.\n");
  exit(0);
}
