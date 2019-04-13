#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main(int argc, char *argv[]) {

    int mainPid = (int) getpid();
    printf("hello world (pid:%d)\n", mainPid);

    int rc = fork();

    printf("rc %d \n", rc);

     if (rc < 0) { // fork failed; exit
         fprintf(stderr, "fork failed\n");
         exit(1);
     } 
     else if (rc == 0) { // child (new process)
        
         printf("hello, I am child (pid:%d)\n", (int) getpid());
         char *myargs[3];
         myargs[0] = strdup("wc"); // program: "wc" (word count)
         myargs[1] = strdup("testing.txt"); // argument: file to count
         myargs[2] = NULL; // marks end of array
        
         execvp(myargs[0], myargs); // runs word count
         printf("this shouldn’t print out");


     } else { // parent goes down this path (main)

        //wait(): it is quite useful for a parent to wait for a child process to finish what it has been doing
        int rc_wait = wait(NULL);

        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }

     return 0;
}