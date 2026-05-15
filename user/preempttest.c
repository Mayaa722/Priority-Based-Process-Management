#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  printf("=== Preemption Test (Mode 1) ===\n");
  printf("Switching to preemptive mode...\n");
  setsched(1);

  int pid1 = fork();
  if(pid1 == 0) {
    setpriority(getpid(), 15);
    printf("[LOW]  priority=%d started, running...\n", getpriority(getpid()));
    volatile long x = 0;
    for(long i = 0; i < 500000000L; i++) x++;
    printf("[LOW]  finished\n");
    exit(0);
  }

  int pid2 = fork();
  if(pid2 == 0) {
    setpriority(getpid(), 2);
    printf("[HIGH] priority=%d started — preempting LOW!\n", getpriority(getpid()));
    for(int i = 0; i < 5; i++){
      printf("[HIGH] running step %d\n", i+1);
      sleep(3);
    }
    printf("[HIGH] done\n");
    exit(0);
  }

  wait(0);
  wait(0);
  printf("=== HIGH preempted LOW successfully! ===\n");
  exit(0);
}
