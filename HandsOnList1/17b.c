#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int fd ; 
	if(fd=open("db.txt",O_RDWR)){
			perror("program");
	}
	struct flock flk;
	flk.l_type = F_WRLCK;
	flk.l_whence = SEEK_SET;
	flk.l_start = 0 ;
	flk.l_len = 0;
	flk.l_pid = getpid();
	printf("Before Critical Section\n");
	if(fcntl(fd , F_SETLKW,&flk) <0){
		perror("Lock");
	}
	printf("Press Enter to reserve a ticket no . \n");
	getchar();
	int buff;
	read(fd, &buff,sizeof(int));
	lseek(fd,0,SEEK_SET);

	 buff++;
	printf("You got the ticket number : %d \n", buff);
	write(fd , &buff , sizeof(int));
	flk.l_type = F_UNLCK;
	fcntl(fd , F_SETLKW , &flk);
	close(fd);
	return 0;
}

	


	



