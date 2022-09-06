#include<stdio.h>
#include<unistd.h>
int main()
{
	char * env[] = {
		"HOME: /home/samir",
		NULL

	};
	if(execle("/bin/ls","ls","-Rl",(char*)NULL , env)<0){
		perror("program");
	}
	return 0 ;
}

	
