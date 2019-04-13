#include <stdio.h> 
#include <sys/types.h>  // sys calll 
#include <unistd.h> 


int main(int argc, char*argv[]) 
{ 
    char* name = argv[0];
    int childpid1 =  fork();

    if ( childpid1 == 0) { 
        printf("child of %s is  %d\n", name, getpid());   
    } 
    else { 
        // sleep(2);   // timer interrupt 
        printf("my child is %d\n", childpid1);  
    } 
    return 0; 
} 
