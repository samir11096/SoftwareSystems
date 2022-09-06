#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	struct flock flk;
	int fd = open("example.txt" , O_RDWR);
	flk.l_type = F_RDLCK;
	flk.l_whence = SEEK_SET;
	flk.l_start = 	0;
	flk.l_len = 0 ;
	flk.l_pid = getpid();
	printf("Before entering into the critical section \n");
	fcntl(fd ,F_SETLKW,&flk);
	printf("Insdie the critical section..\n");
	printf("Enter to unlock\n");
	getchar();
	printf("unlocked\n");
	flk.l_type = F_UNLCK;
	fcntl(fd ,F_SETLKW,&flk);
	printf("finish\n");
	return 0;
}
	

	
	


