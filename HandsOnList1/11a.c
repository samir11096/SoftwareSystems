#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd1 = open("example.txt" , O_RDONLY| O_EXCL);

	// we know the file discriptor 0 - > stdin  , 1 -> stdout , 2 -> stderror
	// Now fd1 must be assigned to 3 as its the lower file discriptor value
	
	if(fd1<0)
	{
		perror("program");
	}


	int fd2 = dup(fd1); // fd 2 must be 4 with will be pointing to dup file itself

	if(fd2<0){
		perror("program");
	}

	printf("The old file discriptor value is %d \n.",fd1);

	printf("The new file discriptor value is %d \n." , fd2);

	return 0;

}



