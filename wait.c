#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("In parent process. Child process complete.\n");
    }

    return 0;
}
