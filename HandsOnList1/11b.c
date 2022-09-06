#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd1 , fd2;

	if((fd1 = open("example.txt" , O_RDONLY ))<0){
		perror("program");
	}

	if((fd2 = dup2(fd1 , 7))<0){ // using dup2 we can assigned our choice of file discriptor value
		perror("program");
	}

	printf("The old file discriptor value is %d . \n " , fd1);
	printf("The new file discriptor value is %d . \n " , fd2);
	return 0;


	
}

		


