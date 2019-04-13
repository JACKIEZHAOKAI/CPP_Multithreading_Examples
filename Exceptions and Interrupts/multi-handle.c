#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

int globalvar = 0;

void signal_me (int signum, siginfo_t *si, void *context)
{
    if (si->si_signo == SIGFPE && si->si_code == FPE_INTDIV) {
	printf ("zoinks! divide by zero\n");
	// trigger another exception/signal
	kill (getpid (), SIGINT);
	// if recursive, then the following line does not execute
	globalvar = 1;
    } else if (si->si_signo == SIGINT) {
	printf ("zoinks! who interrupted us? (globalvar %d)\n", globalvar);
    } else {
	printf ("unexpected signal %d\n", si->si_signo);
    }
    exit (-1);
}

int main (int argc, char *argv[])
{
    struct sigaction sigact;
    int x = 0;

    sigact.sa_sigaction = signal_me;
    sigact.sa_flags = SA_SIGINFO | SA_RESTART;
    if (sigaction (SIGFPE, &sigact, NULL) != 0) {
	printf ("sigaction returned error %d\n", errno);
    }
    if (sigaction (SIGINT, &sigact, NULL) != 0) {
	printf ("sigaction returned error %d\n", errno);
    }
    // we have registered our handler for arithmetic exceptions,
    // now let's trigger it
    return 1/x;
}
