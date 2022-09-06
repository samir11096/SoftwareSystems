/*Question-> Write a program to create a file and print the file descriptor value. Use creat ( ) system call
 *
 * Name -> Samir Ahmed Ghouri Roll-> MT2022100
 * */
#include<stdio.h>
#include<fcntl.h>
int main()
{
	int fd = creat("a.txt",0744);
	if(fd == -1)
	{
		perror("program");
	}
	else{
		printf("File Created Successfully");
	}
	return 0;
}
