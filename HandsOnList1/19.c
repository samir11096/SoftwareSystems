#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>

unsigned long long rdtsc(){
	unsigned long long dst;
	__asm__ __volatile__("rdtsc" :"=A" (dst));
}

int main(void){
	int i , nano;
	unsigned long long int start ,end ;
	start = rdtsc();

	getpid();

	end =rdtsc();

	nano =(end - start)/1.8;

	printf("The time taken is %d ns  .\n", nano);
	return 0;
}
