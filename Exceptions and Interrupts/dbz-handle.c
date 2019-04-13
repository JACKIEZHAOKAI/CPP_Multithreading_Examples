#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

void
signal_me (int signum, siginfo_t *si, void *context)
{
    /* we are looking for an integer divide-by-zero exception */
    if (si->si_signo == SIGFPE && si->si_code == FPE_INTDIV) {
    printf ("zoinks! divide by zero\n");
    } else {
    printf ("unexpected signal %d\n", si->si_signo);
    }
    exit (-1);
}

int
main (int argc, char *argv[])
{
    struct sigaction sigact;
    int x = 0;

    sigact.sa_sigaction = signal_me;
    sigact.sa_flags = SA_SIGINFO | SA_RESTART;
    
    if (sigaction (SIGFPE, &sigact, NULL) != 0) {
    printf ("sigaction returned error %d\n", errno);
    }
    // we have registered our handler for arithmetic exceptions,
    // now let's trigger it
    return 1/x;
}