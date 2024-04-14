#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("In child process. Child PID is %d\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        printf("In parent process with PID %d\n", getpid());
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
