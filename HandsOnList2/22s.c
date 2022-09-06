/*Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Name -> Samir Ahmed Ghouri
Roll-> MT2022100
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/select.h>
#include<unistd.h>
#include<string.h> 
#include<sys/stat.h>
int main()
{

    int fd;
    char * myfifo = "myfifo";
    mkfifo(myfifo,0666);
    char buff[100];
	printf("Enter a string to be send within 10 seconds: ");
	scanf("%s",buff);
/* open, read, and display the message from the FIFO */
    	fd = open(myfifo, O_WRONLY);
    	write(fd, buff, strlen(buff));
    	close(fd);
	return 0;
}
	
