#include<stdio.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	fd_set rd;
	struct timeval tv;
	int err;
	FD_ZERO(& rd);
	FD_SET(0,&rd);
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	err = select(1,&rd ,NULL,NULL , & tv);
	if(err==0){
		printf("No input given in 10 seconds.\n");
	}
	else if(err>0){
		printf("Out put given");
	}
	else{
		perror("program");
	}
	return 0;
}
