#include<stdio.h>
#include<unistd.h>
int main()
{
	//the executable file is stored in the previous directory named test2 
	if(execl(".././test2","./test2" ,"SomeInputString", (char *)NULL)<0){
		perror("program");
	}
	return 0;
}
