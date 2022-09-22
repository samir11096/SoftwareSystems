/* Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
 *
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 * */


#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main()
{
	int child , parent;

	child = fork();
	if(!child){
		parent = getppid();
		if(kill(parent, SIGKILL)<0)
		{
			perror("Error while sending SIGKILL to parent\n");
		}
		else{
			printf("Kill Parent Successfully.\n");
			sleep(5);
			printf("Child Process Completed.\n");
		}
	}
	else{
		sleep(10);
	}
	return 0;
}

