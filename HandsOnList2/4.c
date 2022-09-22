/*Write a program to measure how much time is taken to execute 100 getppid ( ) system call. Use time stamp counter.
 *
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 *
 * */

#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>

unsigned long long rdtsc(){
	unsigned long long dst;
	__asm__ __volatile__("rdtsc" :"=A" (dst));
}

int main(void){
	int  nano;
	unsigned long long int start ,end ;
	int i = 0;
	int ppid = 0;
	start = rdtsc();
	while(i<100){
		ppid = getppid();
		i++;
	}
	end =rdtsc();

	nano =(end - start)/1.8;

	printf("The time taken is %d ns  .\n", nano);
	return 0;
}
