/*Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).

Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/

#include<fcntl.h>
#include <unistd.h>    
#include <sys/types.h> 
#include <sys/stat.h>  
#include <stdio.h> 
#incl

int main()
{

	long max_no_files = sysconf(_SC_OPEN_MAX);

	if(max_no_files<0){
		perror("sysconf program");
	}
	printf("Maximum Number of files that can be opened within a process is %ld.\n",max_no_files);

	//creating a pipe 
	int fd[2];
	pipe(fd);
	//How to find the circular buffer 
	int size = fcntl(fd ,  F_GETPIPE_SZ );
	return 0;
}
