#include "kernel/types.h"
#include "user/user.h"

int main(void) {
    char message[] = "Hello from child process!";

    // Create pipe before fork
    int fd[2];
    if (pipe(fd) < 0) {
        printf("pipe failed\n");
        exit(1);
    }

    int pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child: close read end, write message
        close(fd[0]);
        write(fd[1], message, strlen(message));
        close(fd[1]);
        exit(0);
    } else {
        // Parent: close write end, read message
        close(fd[1]);

        char buffer[100];
        int n = read(fd[0], buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';
        close(fd[0]);

        write(1, buffer, strlen(buffer));
        write(1, "\n", 1);

        wait(0);
    }

    exit(0);
}
