#include<stdio.h>
#include<fcntl.h>

int main()
{
	int fd1 , fd2;
	if((fd1= open("example.txt",O_RDONLY))<0){ // this will take the value of 3
		perror("program");
	}

	if((fd2 = fcntl(fd1 , F_DUPFD))<0){  // this works exaclty like dup and not dup2 i.e. it will take the value of the lowest file descriptor
		perror("While duplicating");
	}

	printf("The old file desciptor %d . \n " , fd1);
	printf("The new file descriptor %d.\n" ,fd2);
	return 0;
}


	
