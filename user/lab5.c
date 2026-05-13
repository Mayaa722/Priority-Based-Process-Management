#include "kernel/types.h"
#include "user/user.h"

int main(void) {
    printf("Parent process (pid: %d) waiting for child...\n", getpid());

    int pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (pid: %d) is running ls...\n", getpid());

        char *args[] = { "ls", 0 };
        exec("ls", args);

        // If exec returns, it failed
        printf("exec failed\n");
        exit(1);
    } else {
        // Parent process
        wait(0);
        printf("Child process finished. Parent continuing.\n");
    }

    exit(0);
}
