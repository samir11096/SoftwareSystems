#include<stdio.h>
#include<unistd.h>
int main()
{	
	if(execl("/bin/ls","ls","-Rl",(char *)NULL)<0){
		perror("program");
	}
	//this line should not be executed since it overwrite the process image
	printf("This should not be executed");
	return 0;
}
