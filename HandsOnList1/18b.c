#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	struct tk{
		int ticket_number;
	};

	struct tk arr_tk[3];
	for(int i = 0 ; i<3 ;i++){
		arr_tk[i].ticket_number = i;
	}
	//creating 3 reacord in a file
	int fd ;
	if((fd=open("ticket.txt",O_CREAT|O_RDWR , 0744))<0){
		perror("program");
	}
	
	write(fd, arr_tk , sizeof(arr_tk));
	lseek(fd,0,SEEK_SET);

	//defining struct flock
	int record_to_access ;	
	struct flock flk = {F_UNLCK, SEEK_SET, 0 ,0,getpid()};
	printf("Enter recored to access :");
	scanf("%d",&record_to_access);
	int n =sizeof(struct tk);
	if(record_to_access ==1){
		flk.l_type =F_RDLCK;
		flk.l_whence = SEEK_SET;
		flk.l_start = 0;
		flk.l_len = sizeof(n);
		flk.l_pid = getpid();
	}
	else if (record_to_access ==2){

		flk.l_type =F_RDLCK;
		flk.l_whence = SEEK_SET;
		flk.l_start = sizeof(n);
		flk.l_len = sizeof(n);
		flk.l_pid = getpid();
	}
	else if(record_to_access ==3){
		flk.l_type =F_RDLCK;
		flk.l_whence = SEEK_SET;
		flk.l_start = sizeof(2*n);
		flk.l_len = sizeof(n);
		flk.l_pid = getpid();
	}

	printf("Before locking the record %d\n",record_to_access);
	if(fcntl(fd,F_SETLKW,&flk)){
		perror("lock");
	}
	printf("Recored %d accessed.\n",record_to_access);
	getchar();
	printf("Enter to unlock\n");
	getchar();
	flk.l_type = F_UNLCK;
	if(fcntl(fd ,F_SETLKW ,&flk))
	{
		perror("unlock");
	}
	printf("Record %d unlocked successfully\n",record_to_access);
	return 0;
}
