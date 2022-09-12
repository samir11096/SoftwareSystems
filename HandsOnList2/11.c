/*Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -use sigaction system call.
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 * */


#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	//PART1 ignoring the signal
	struct sigaction st;

	st.sa_handler = SIG_IGN;
	if(sigaction(SIGINT, &st,NULL)<0){
		perror("signal program");
	}

	printf("Ignoring SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 seconds\n");

	//PART2 reseting the default action of the SIGINT
	st.sa_handler = SIG_DFL;

	if(sigaction(SIGINT,&st , NULL)<0)
	{
		perror("signal program");
	}
	printf("Default action for SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 seconds\n");

	return 0;
}



