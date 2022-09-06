#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("Parent process id %d \n", getpid());
	fflush(stdout);
	int child = fork();
	if(child!=0)
	{
		printf("Entering Zombie state...\n");
		sleep(10);
		printf("Zombie state exited.\n");
	}
	return 0;
}

