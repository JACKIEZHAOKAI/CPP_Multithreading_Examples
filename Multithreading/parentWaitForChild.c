#include <stdio.h>  
#include <pthread.h>
#include <sys/types.h> 
#include <unistd.h> 
volatile int done = 0;

void *child(void *arg) {
printf("child\n");
done = 1;
return NULL;
}

int main(int argc, char *argv[]) {
     printf("parent: begin\n");
     pthread_t c;
     pthread_create(&c, NULL, child, NULL); // create child
     while (done == 0)
     ; // spin
     printf("parent: end\n");
     return 0;
 }
