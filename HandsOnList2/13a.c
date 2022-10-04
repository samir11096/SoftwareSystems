/*Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not. 
 *
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 *
 * */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void my_handler (int sig);

int main()
{
	printf("The pid of the running process is %d.\n", getpid());
	if(signal(SIGSTOP,my_handler)<0){
		perror("signal program");
	
	}
	sleep(20);
	return 0;
}

void my_handler(int sig){
	printf("Got SIGSTOP , number %d.\n",sig);
}
