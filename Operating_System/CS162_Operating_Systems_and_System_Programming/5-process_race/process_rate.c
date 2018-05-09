
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
    pid_t cpid, mypid;
    int i;

    // Clone a child process and get child pid
    cpid = fork();

    // Running parent
    if(cpid > 0) {
        mypid = getpid();
        printf("[%d] parent of [%d] \n", mypid, cpid);

        // Race: parent
        for(i=0; i<100; ++i) {
        	printf("[%d] parent: %d\n", mypid, i);
        }
    }

    // Running child
    else if(cpid == 0) {
        mypid = getpid();
        printf("[%d] child\n", mypid);

        // Race: child
        for(i=0; i>-100; --i) {
        	printf("[%d] child: %d\n", mypid, i);
        }
    }

    // Error
    else {
        perror("Fork failed");
        exit(1);
    }

    exit(0);
}
