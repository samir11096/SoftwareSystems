/*Write a separate program using sigaction system call to catch the following signals.
 * b.SIGINT
 *
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 * */

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>


void my_handler (int sig);

int main()
{

	struct sigaction st;

	st.sa_handler = my_handler;

	int ret = sigaction(SIGINT, &st ,NULL);

	if(ret<0){
		perror("signal program");
	}
	else{
		printf("Catching SIGINT\n");
		raise(SIGINT);
	
	}
	return 0;
}

void my_handler(int sig){
	printf("Got SIGINT , number %d.\n",sig);
}

