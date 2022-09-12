/*Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
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
	signal(SIGINT ,SIG_IGN);
	printf("Ignoring SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 seconds\n");

	//PART2 reseting the default action of the SIGINT
	signal(SIGINT,SIG_DFL);
	printf("Default action for SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 seconds\n");

	return 0;
}



