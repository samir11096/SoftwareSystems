#include<stdio.h>
#include<unistd.h>
int main()
{
	char * arg[]={
		"ls",
		"-Rl",
		NULL
	};
	// will search in the path variable of env for ls
	if(execvp("ls",arg)<0){
		perror("program");
	}
	return 0;
}
