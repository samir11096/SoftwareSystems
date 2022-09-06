#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int  ticket_no = 55;// see how i am storing integer value in the file.Check the files also.
	int fd ; 
	int * ptn = &ticket_no;
	fd = open("db.txt",O_CREAT|O_RDWR,0744);
	write(fd,ptn , sizeof(ticket_no));
	printf("%p\n",ptn);
	close(fd);
	int fd1 = open("db.txt",O_RDONLY);
	int buff;
	read(fd1 ,&buff,sizeof(int));
	printf("%d",buff);
	return 0;
}
		
