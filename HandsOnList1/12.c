#include<stdio.h>
#include<fcntl.h>

int main()
{
	int fd , open_fl;
	if((fd =open("example.txt",O_RDWR ))<0){

		perror("program");
	}

	 open_fl = fcntl(fd , F_GETFL );
	 printf("%d file descriptor has %d flags.\n", fd , open_fl);//You are getting back o100002, which is a combination of the O_RDWR (o2) and O_LARGEFILE (o100000) flags. Convert 100002 to decimal and you will get the output.

	 return 0 ;
}




