#include<stdio.h>
#include<unistd.h>
int main()
{
	char * arg[] = {
		"ls",
		"-Rl",
		NULL
	};

	if(execv("/bin/ls",arg)<0){
		perror("program");
	}
	return 0;
}
