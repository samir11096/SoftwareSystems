
/*Write a separate program using signal system call to catch the following signals.
f. SIGVTALRM (use setitimer system call)
Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>


void my_handler (int sig);

int main()
{
	struct itimerval tm;
	tm.it_interval.tv_sec = 0;
	tm.it_interval.tv_usec = 0;
	tm.it_value.tv_sec = 2;
	tm.it_value.tv_usec = 0;

	if(signal(SIGVTALRM,my_handler)<0){
		perror("signal program");
	
	}
	else{
		printf("Catching SIGVTALRM\n");
		//raise(SIGALRM);
		if(setitimer(ITIMER_VIRTUAL,&tm,0)<0){
			perror("setitimer program");
		}
	//	sleep(5);
	
		while(1); // sleep not working as the process needs to be active 
	}
	return 0;
}

void my_handler(int sig){
	printf("Got SIGVTALRM , number %d.\n",sig);
	//exiting from the main execution of the program
	exit(0);
}

