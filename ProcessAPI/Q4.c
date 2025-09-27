#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child (PID %d): About to execute /bin/ls...\n", getpid());
        
        // execlp: uses PATH search, arguments passed as a list.
        // The first argument ("ls") is traditionally the name of the program.
        execlp("ls", "ls", "-l", NULL);
        
        // exec calls do not return on success. If this line is reached, exec failed.
        perror("execlp failed");
        exit(1); 
    } else {
        // Parent process
        printf("Parent (PID %d): Waiting for child (PID %d) to finish.\n", getpid(), pid);
        wait(NULL);
        printf("Parent: Child finished, program complete.\n");
    }

    return 0;
}