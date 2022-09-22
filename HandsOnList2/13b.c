/* Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
 *
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 *
 * */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int pid = atoi(argv[1]);

	if(kill(pid,SIGSTOP)<0){
		perror("SIGSTP Program");
	}
	else{
		printf("Successfully sent SIGSTOP signal to process %d .\n",pid);
	}
	return 0;
}
