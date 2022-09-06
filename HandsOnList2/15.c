/*Write a simple program to send some data from parent to the child process.
 * Name -> Samir Ahmed Ghouri
 * Roll-> MT2022100
 * */

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>


int main()
{
	int fd[2];
	char buff[100];
	pipe(fd);
	if(fork()){
		close(fd[0]); 
		int size_w =write(fd[1],"Sending some data.",19);
		wait(0);
	}
	else{
		close(fd[1]);
		read(fd[0],&buff,19);
		printf("Data received at child process is \"%s\".\n",buff);
	}
	return 0;
}

