#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: myfirstprogram <ticks>\n");
        exit(1);
    }
    long int ticks = atoi(argv[1]);
    pause(ticks);
    printf("done sleeping for %ld ticks\n", ticks);
    exit(0);
}
