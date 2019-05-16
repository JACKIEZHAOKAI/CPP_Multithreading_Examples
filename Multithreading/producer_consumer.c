//#######################################################
// Producer/Consumer using two CV 

// Imagine one or more producer threads and one or more consumer threads. 

// Producers generate data items and place them in a buffer; 
// consumers grab said items from the buffer and consume them in some way.

// This arrangement occurs in many real systems. 
// For example, in a multi-threaded web server, a producer puts HTTP requests into a work queue 
// (i.e., the bounded buffer); consumer threads take requests out of this queue and process them

//#######################################################
// Now we need to write some routines that know when it is OK to access
// the buffer to either put data into it or get data out of it. 
// The conditions for this should be obvious: 
//      only put data into the buffer when count is zero
//      and only get data from the buffer when count is one
//#######################################################
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int buffer[100];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % 100;
    count++;
}


int get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % 100;
    count--;
    return tmp;
}


pthread_cond_t empty, fill;     
pthread_mutex_t mutex;

void *producer(void *arg) {
	int i;
	for (i = 0; i < 100; i++) {
		pthread_mutex_lock(&mutex); 
		
        //check if the buffer is full, if full then can not put more into buffer
        while (count == 100)        // using a while to check is always safer than using if
		{
            printf("buffer is full, Producer thread waiting for consumer to take something from buffer");
            pthread_cond_wait(&empty, &mutex); 
        }

        // accessing the buffer(shared var)
		put(i); // only put data into the buffer when the buffer is empty
        printf("Producing value : %d" + i);

		pthread_cond_signal(&fill); // wake()
		
        pthread_mutex_unlock(&mutex); 
        
	}
}


void *consumer(void *arg) {
	int i;
	for (i = 0; i < 100; i++) {
		pthread_mutex_lock(&mutex); 

        //check if the buffer is empty, if empty then can not get from the buffer
		while (count == 0)     
		{
            printf("buffer is empty, consumer thread waiting for producer thread put sth into buffer");
            pthread_cond_wait(&fill, &mutex); 
        }	
		
        int tmp = get(); // only get data from the buffer when the buffer is full
		printf("consuming value:  %d\n", tmp);

        pthread_cond_signal(&empty); 

        pthread_mutex_unlock(&mutex);
	}
}


int main(int argc, char *argv[]) {
    
    printf("Solving Producer Consumper Problem\n");

    pthread_t t1, t2;

    pthread_create(&t1, NULL, producer, argv);
    pthread_create(&t2, NULL, consumer, argv);
    
    return 0;
}













