#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	printf("Parent process id is %d\n",getpid());
	fflush(stdout);
	int child = fork();
	while(child == 0)
	{
		printf("Orphan process created with process id %d\n",getpid());
		sleep(10);
		fflush(stdout);
		printf("Orphan process terminated ");
		exit(0);
	}
	return 0;
}
