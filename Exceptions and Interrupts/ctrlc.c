#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

void signal_me (int signum, siginfo_t *si, void *context)
{
    /* we are looking for a program interrupt signal */
    if (si->si_signo == SIGINT) {
        printf ("zoinks! who interrupted our sleep?\n");
    } else {
        printf ("unexpected signal %d\n", si->si_signo);
    }
}

int main (int argc, char *argv[])
{
    struct sigaction sigact;
    int x = 0;

    sigact.sa_sigaction = signal_me;
    sigact.sa_flags = SA_SIGINFO | SA_RESTART;

    // sigaction() returns 0 on success; on error, -1
    if (sigaction (SIGINT, &sigact, NULL) != 0) {
        printf ("sigaction returned error %d\n", errno);
    }
    // we have registered our handler for SIGINT
    // now let's go to sleep waiting for someone to interrupt us
    sleep (100);
    return 0;
}