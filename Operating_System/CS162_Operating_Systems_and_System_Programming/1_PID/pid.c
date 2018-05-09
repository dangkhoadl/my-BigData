
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {

    // Get current Process PID
    pid_t pid = getpid();
    printf("My pid: %d\n", pid);

    exit(0);
}
