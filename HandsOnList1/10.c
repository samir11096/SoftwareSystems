#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>


int main()
{
	int fd = open("example.txt", O_RDWR);

	if(fd<0){
		perror("program");
	}
	char buff[100] = "samirahmedghouri";

	write(fd ,buff , 10);

	int lp = lseek(fd , 10 , SEEK_CUR);

	write(fd , buff , 10);

	printf("Return value of lseek is %d \n ", lp);
	return 0;
}

