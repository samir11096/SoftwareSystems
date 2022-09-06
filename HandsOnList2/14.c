/*Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor. 
 * Name-> Samir Ahmed Ghouri 
 * Roll-> MT2022100
 * */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd[2];
	char buff[100];
	pipe(fd);
	int size_w= write(fd[1],"Hello, How are you?",20);
	int size_r= read(fd[0], &buff ,size_w);
	write(1,&buff,size_r);
	printf("\n");
	return 0;
}

