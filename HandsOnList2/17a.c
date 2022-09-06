/* Write a program to execute ls -l | wc.
a. use dup

Name -> Samir Ahmed Ghouri 
Roll -> MT2022100
*/

#include<stdio.h>
#include<unistd.h>

int main()
{
	int fd[2];
	pipe(fd);
	if(!fork())
	{
		//close std out
		close(1);
		//std out replace with pipe write end
		dup(fd[1]);
		//closing read end of child pipe
		close(fd[0]);
		execlp("ls","ls","-l",(char *)NULL);
	}
	else{
		// closing std in
		close(0);
		// std in replace with pipe read end
		dup(fd[0]);

		close(fd[1]);
		execlp("wc","wc",(char * ) NULL);
	}
	return 0;
}

