#include <stdio.h>  
#include <pthread.h>
#include <sys/types.h> 
#include <unistd.h> 
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void thread_exit() {
    pthread_mutex_lock(&m);
    
    done = 1;
    pthread_cond_signal(&cv);        // wake()

    pthread_mutex_unlock(&m);
 }

 void *child(void *arg) {
     printf("running child\n");
     thread_exit(); // call pthread_cond_signal(&cv) to wake up main thread
     return NULL;
 }

 void thread_join() {
     pthread_mutex_lock(&m);
 
     while (done == 0)  
     pthread_cond_wait(&cv, &m);     // wait()

     pthread_mutex_unlock(&m);
 }

 int main(int argc, char *argv[]) {
     printf("parent: begin\n");
     pthread_t p;
     pthread_create(&p, NULL, child, NULL);

     // Althernative is using spin, but parent/main thread wasting CPU
     //      while (done == 0)
     // ; // spin

     // Only set done to 1 in child
    //  void *child(void *arg) {
    //     printf("child\n");
    //     done = 1;
    //     return NULL;
    // }

     thread_join(); // parent wait until child thread completed
  
     printf("parent: end\n");
     return 0;
 }






