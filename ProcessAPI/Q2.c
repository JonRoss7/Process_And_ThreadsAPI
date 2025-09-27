#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    // Open a file for writing, creating it if it doesn't exist
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child writes to the file
        char *child_msg = "CHILD_WRITE\n";
        for (int i = 0; i < 3; i++) {
            write(fd, child_msg, strlen(child_msg));
            usleep(10000); // Small delay for interleaving
        }
    } else {
        // Parent writes to the file
        char *parent_msg = "PARENT_WRITE\n";
        for (int i = 0; i < 3; i++) {
            write(fd, parent_msg, strlen(parent_msg));
            usleep(10000); // Small delay for interleaving
        }
        wait(NULL);
        close(fd);
    }

    return 0;
}