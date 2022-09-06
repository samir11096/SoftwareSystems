/*Write a program to execute ls -l | wc.
 * c. use fcntl
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT20222100
 * */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd[2];
	pipe(fd);

	if(!fork())
	{
		fd[1]=fcntl(1, F_SETFD);//notworking 
		close(fd[0]);
		//execlp("ls","ls","-l",(char*)0);
	}
	else{
		fd[0] = fcntl(0,F_SETFD);
		close(fd[1]);
		//execlp("wc","wc",(char*)0);
	}
	return 0;
}

		
		
