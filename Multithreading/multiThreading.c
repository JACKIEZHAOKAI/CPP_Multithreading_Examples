#include <stdio.h>
#include <pthread.h>
static volatile int counter = 0;    // shared var among threads
// volatile makes the static var can be changed after defined

void*  mythread(void *arg)
{
    printf("%s: begin thread with counter %d\n", (char *) arg, counter);
    int i;
    for (i = 0; i < 10e6; i++) {  // by increamenting 10 t0 1e7 and you will be surprised to see an undertermined result of the counter(shared var among threads)
         counter = counter + 1;
        // printf("%s increment counter =  %d\n", (char*)arg ,counter);
    }
    
    printf("%s: end thread with counter %d \n", (char *) arg, counter);
    return 0;
}

int main(int argc,char* argv[]){
    pthread_t p1 ,p2;

    printf("(main begin counter = %d)\n",counter );

    // pthread_create - create a new thread
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
    // http://man7.org/linux/man-pages/man3/pthread_create.3.html
    // pthread_create(&tid, NULL, myThreadFun, (void *)&tid); 
    
    // passing argu to pthread funciton, can pass more para 
    // http://www.cse.cuhk.edu.hk/~ericlo/teaching/os/lab/9-PThread/Pass.html
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    

    // join waits for the threads to finish, main thread  for child thread
    // otherwise if main thread ends before then problematic
    
    // pthread_join - join with a terminated thread
    //int pthread_join(pthread_t thread, void **retval);
    //http://man7.org/linux/man-pages/man3/pthread_join.3.html
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("main: done with both (counter = %d)\n", counter);
    return 0;
}
