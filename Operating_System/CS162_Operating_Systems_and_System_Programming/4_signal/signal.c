
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include <unistd.h>
#include <signal.h>

void signal_callback_handler(int signum) {
    printf("Caught signal %d\n", signum);
    exit(1);
}

int main(int argc, char *argv[]) {

    // Catch an interrupt and send a signal to signal_callback_handler
    signal(SIGINT, signal_callback_handler);

    while(1);
}
