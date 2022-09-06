#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("Parent process id %d\n.",getpid());
	fflush(stdout);
	int child = fork();
	if(child==0){
		printf("Child processs id %d\n.",getpid());
	}
	return 0;
}
		
