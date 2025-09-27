#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    int status;
    pid_t wpid;

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child (PID %d): Running and will exit after 2 seconds.\n", getpid());
        sleep(2);
        exit(0);
    } else {
        // Parent process
        printf("Parent (PID %d): Checking for child (PID %d) using waitpid() with WNOHANG.\n", getpid(), pid);

        // Loop to periodically check on the child
        do {
            // wpid will be 0 if the child hasn't terminated (WNOHANG is set)
            wpid = waitpid(pid, &status, WNOHANG); 

            if (wpid == 0) {
                printf("Parent: Child is still running. Doing other work...\n");
                sleep(1);
            }
        } while (wpid == 0); // Loop while child is running

        // When wpid > 0, the child terminated
        if (wpid == pid) {
            printf("Parent: waitpid() returned PID %d. Child is done.\n", wpid);
        } else {
            // This should only happen if there was an error (wpid == -1)
            perror("waitpid failed unexpectedly");
        }
    }

    return 0;
}