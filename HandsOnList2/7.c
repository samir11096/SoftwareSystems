/*Write a simple program to print the created thread ids.
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
	pthread_t mythread ;

	if(pthread_create( &mythread, NULL, (void *) thread_func, NULL)<0){
		perror("Error while creating thread one");
	}
	// Wait for the threads to terminate and then terminate the main process
    	pthread_exit(NULL);
	return 0;
}
