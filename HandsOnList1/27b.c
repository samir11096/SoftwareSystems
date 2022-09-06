#include<stdio.h>
#include<unistd.h>
int main()
{	
	//it searches for the file (1st argument of execlp) in those directories pointed by PATH i.e the environment variable
	if(execlp("ls" , "ls" ,"-Rl",(char*)NULL)<0){
		perror("program");
	}
	return 0;
}
