#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    pid_t pid = fork();
    int status;
    pid_t wpid;

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child (PID %d): Running and will exit after 1 second.\n", getpid());
        sleep(1);
        
        // Child attempts to call wait()
        wpid = wait(&status);
        if (wpid == -1 && errno == ECHILD) {
            printf("Child (PID %d): wait() returned %d (Error: No children to wait for).\n", getpid(), wpid);
        } else {
             printf("Child (PID %d): wait() returned %d (Unexpected).\n", getpid(), wpid);
        }

        exit(123); // Exit with a specific status
    } else {
        // Parent process
        printf("Parent (PID %d): Waiting for child (PID %d).\n", getpid(), pid);
        
        // Parent calls wait()
        wpid = wait(&status);
        
        // wait() returns the PID of the terminated child
        printf("Parent: wait() returned PID %d (the child that terminated).\n", wpid);
    }

    return 0;
}