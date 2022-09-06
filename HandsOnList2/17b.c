/* Write a program to execute ls -l | wc.
 * b. use dup2
 * Name -> Samir Ahmed Ghouri
 * Roll-> MT2022100
 * */

#include<stdio.h>
#include<unistd.h>
int main()
{
	int fd[2];
	pipe(fd);
	
	if(!fork())
	{
		dup2(fd[1],1);
		close(fd[0]);
		execlp("ls","ls","-l",(char *)0);
	}else{
		dup2(fd[0],0);
		close(fd[1]);
		execlp("wc","wc",(char*)0);
	}
	return 0;
}
