/*Write a program to send and receive data from parent to child vice versa. Use two way communication.
 * Name-> Samir Ahmed Ghouri
 * Roll-> MT2022100
 * */

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int fd_p_to_c[2];
	int fd_c_to_p[2];
	char buff[100];
	pipe(fd_p_to_c);
	pipe(fd_c_to_p);

	if(fork()){
		close(fd_p_to_c[0]);
		close(fd_c_to_p[1]);
		write(fd_p_to_c[1] , "Data from Parent", 17);
		printf("Parent Reading ..\n");
		read(fd_c_to_p[0],&buff,16);
		printf("Parent Read : %s\n",buff);
		wait(0);
	}
	else{
		close(fd_p_to_c[1]);
		close(fd_c_to_p[0]);
		write(fd_c_to_p[1],"Data from Child",16);
		printf("Child Reading ..\n");
		read(fd_p_to_c[0],&buff,17);
		printf("Child Read : %s\n",buff);
	}
	return 0;
}
