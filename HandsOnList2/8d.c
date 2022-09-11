/*Write a separate program using signal system call to catch the following signals.
d.SIGALRM (use alarm system call)
Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void my_handler (int sig);

int main()
{
	if(signal(SIGALRM,my_handler)<0){
		perror("signal program");
	
	}
	else{
		printf("Catching SIGALRM\n");
		//raise(SIGALRM);
		alarm(2);
		sleep(5);
	}
	return 0;
}

void my_handler(int sig){
	printf("Got SIGALRM , number %d.\n",sig);
}

