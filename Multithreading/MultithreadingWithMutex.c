#include <stdio.h>
#include <pthread.h>
static volatile int counter = 0;    // shared var among threads
// volatile makes the static var can be changed after defined
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // statically alloc mutex lock
//  thread MUST be specified mutex OR CV or...
// only ONE lock is used among many threads, so that only one thread can access the critical section a each time 


void*  mythread(void *arg)
{
   
    printf("%s: begin thread with counter %d \n", (char *) arg, counter);
    int i;


    //thread mutex lock -> only lock the critical section
    //https://linux.die.net/man/3/pthread_mutex_lock
    pthread_mutex_lock(&mutex);
    for (i = 0; i < 1e7; i++) {  
        //critical section    
        counter = counter + 1;
        // printf("%s increment counter =  %d\n", (char*)arg ,counter);
    }
    pthread_mutex_unlock(&mutex);
        
    printf("%s: end thread with counter %d \n", (char *) arg, counter);
    return NULL;
}

int main(int argc,char* argv[]){
    pthread_t p1 ,p2;

    printf("(main begin counter = %d)\n",counter );

    // pthread_create - create a new thread and start Executing 
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
    // http://man7.org/linux/man-pages/man3/pthread_create.3.html
    // pthread_create(&tid, NULL, myThreadFun, (void *)&tid); 
    
    // passing argu to pthread funciton, can pass more para 
    // http://www.cse.cuhk.edu.hk/~ericlo/teaching/os/lab/9-PThread/Pass.html

    pthread_create(&p1, NULL, mythread, "A");
    // pthread_join(p1, NULL);      // A thread join to main() after completed, then NO multi threading

    // after creating and exce A , can CS to main() before calling join(A), Now main() and A thread are running concurently 
    pthread_create(&p2, NULL, mythread, "B");   // B can begins anywhere after
        //waiting to aquire the mutex lock from A,  exec once A release the lock  
    

    // join waits for the threads to finish, main thread  for child thread
    // otherwise if main thread ends before then problematic
    
    // pthread_join - join with a terminated thread
    // in this case, A thread terminated and then join with the main() thread  
    //int pthread_join(pthread_t thread, void **retval);
    //http://man7.org/linux/man-pages/man3/pthread_join.3.html
    pthread_join(p1, NULL);
    printf("counter in main after A done: %d\n", counter);
    // printf("##################### \n A finish and CS to main thread \n");
    pthread_join(p2, NULL);
    // printf("##################### \n B finish and CS to main thread \n");

    printf("main: done with both (counter = %d)\n", counter);
    return 0;
}
