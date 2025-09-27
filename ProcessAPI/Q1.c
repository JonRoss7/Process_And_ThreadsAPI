#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 100;
    pid_t pid;

    printf("Parent (PID %d): Initial value of x is %d\n", getpid(), x);

    pid = fork();

    if (pid < 0) {
        // Error
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child (PID %d): Value of x after fork is %d\n", getpid(), x);
        x = 50; // Child changes its copy
        printf("Child (PID %d): Changed x to %d\n", getpid(), x);
    } else {
        // Parent process
        // Parent waits briefly to let child run and change x
        sleep(1); 
        printf("Parent (PID %d): Value of x after child runs is %d (Unchanged)\n", getpid(), x);
        x = 200; // Parent changes its copy
        printf("Parent (PID %d): Changed x to %d\n", getpid(), x);
        wait(NULL);
    }

    return 0;
}