#include<stdio.h>
#include<unistd.h>
int main()
{
	//file is stored in the previous directory named test
	if( execl(".././test","./test" , (char *) NULL)<0){
		perror("Program");
	}
	return 0;
}
