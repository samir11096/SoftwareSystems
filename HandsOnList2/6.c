/*Write a simple program to create three threads.
 *
 * Name -> Samir Ahmed Ghouri 
 * Roll -> MT2022100
 *
 * */

#include<stdio.h>
#include<pthread.h>

void thread_func(void){
	printf(" Thread id is %ld", pthread_self());
	}

int main() {  
	pthread_t mythread1 , mythread2 , mythread3;

	if(pthread_create( &mythread1, NULL, (void *) thread_func, NULL)<0){
		perror("Error while creating thread one");
	}

	if(pthread_create( &mythread2, NULL, (void *) thread_func, NULL)<0){
		perror("Error while creating thread one");
	}

	if(pthread_create( &mythread3, NULL, (void *) thread_func, NULL)<0){
		perror("Error while creating thread one");
	}
	// Wait for the threads to terminate and then terminate the main process
    	pthread_exit(NULL);
	return 0 ;
 }
