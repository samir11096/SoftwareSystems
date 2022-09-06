/*Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.

Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include<sys/select.h>


#define MAX_BUF 100

int main()
{
	int fd;
	char * myfifo = "myfifo";
	
	char buff[100];

	
	fd = open(myfifo,O_RDONLY);

	fd_set rd;
	struct timeval tv;
	int err;
	FD_ZERO(& rd);
	FD_SET(fd,&rd);
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	printf("%d\n",fd);// why the value of fd is 3 here
	err = select(fd+1,&rd ,NULL,NULL , & tv);
	if(err==0){
		printf("No input given in 10 seconds.\n");
	}
	else if(err>0){
		read(fd,buff,sizeof(buff));
		printf("Successfully Written to the fifo file in 10 secs.\n");
	}
	else{
		perror("program");
	}

    return 0;
}
