#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("hello\n");
        // Ensure the child exits quickly
        exit(0); 
    } else {
        // Parent process
        // Parent waits (non-deterministically) to let child finish
        // Without wait(), this is the only simple way to try to order output
        usleep(100000); // Sleep for 100 milliseconds
        printf("goodbye\n");
    }

    return 0;
}
