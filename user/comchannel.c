#include "kernel/types.h"
#include "user/user.h"

int main() {
  int fds[2];       // pipe file descriptors
  char buf[100];
  int pid;

  // Create the pipe
  pipe(fds);

  pid = fork();

  if(pid < 0){
    printf("Fork failed\n");
    exit(0);
  }

  if(pid == 0){
    // CHILD PROCESS

    close(fds[1]);              // close write end
    read(fds[0], buf, sizeof(buf));
    printf("Child received: %s", buf);
    close(fds[0]);

  } else {
    // PARENT PROCESS

    close(fds[0]);              // close read end
    write(fds[1], "Hello from parent!\n", 19);
    close(fds[1]);
  }

  exit(0);
}
