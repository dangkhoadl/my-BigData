
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    char buf[BUFSIZE];
    size_t readlen, writelen, slen;
    pid_t cpid, mypid;

    // Get current Process PID
    pid_t pid = getpid();
    printf("Parent pid: %lld\n", pid);

    // Clone a child process and get child pid
    cpid = fork();

    // Running parent
    if(cpid > 0) {
        mypid = getpid();
        printf("[%lld] parent of [%lld] \n", mypid, cpid);
    }

    // Running child
    else if(cpid == 0) {
        mypid = getpid();
        printf("[%lld] child\n", mypid);
    }

    // Error
    else {
        perror("Fork failed");
        exit(1);
    }

    exit(0);
}
