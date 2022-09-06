#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd;
	if((fd=open("example.txt",O_CREAT|O_RDWR,0744))<0){
		perror("program");
	}
	char buff[100]="Writing something to the file";
	fork();
	write(fd,buff,30);
	return 0;
}

