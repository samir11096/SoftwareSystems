/* Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore

Name -> Samir Ahmed Ghouri
Roll -> MT2022100

*/

#include <sys/ipc.h>   
#include <sys/sem.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <stdio.h>   

int main()
{
	int fd;
	int readBytes , writeBytes;
	int lseekoffset;
	int status;
	int data;

	//opening a file
	fd = open("ticket.txt",O_RDWR|0666);
	if(fd<0)
	{
		perror("Error while opening the file");
	}
	
	//defining the value of sempahore
	union semun {
		int val;
	} semSet;

	//creating a key for semaphore set
	key_t key = ftok(".",333);
	
	if(key<0){
		perror("Error while creating the key");
	}
	
	//checking if the semaphore set  is already created using flag =0
	int id = semget(key , 1,0);
	if(id<0)
	{
		//if not created , create a new semapore set
		id = semget(key , 1, IPC_CREAT|0777);
		if(id<0){
			perror("Error while creating semaphore set");
		}

		//initialsing the sempahore 
		semSet.val = 1;
		status = semctl(id,0,SETVAL,semSet);//defining the Othe semaphore of semaphore set 
		if(status<0)
		{
			perror("Error while initialising the semaphore");
		}
	}
	
	//sembuf contains sem_num , sem_op, sem_flg
	struct sembuf semOp;
	semOp.sem_num = 0; // semaphore number in the set
	semOp.sem_flg = 0; // default behaviour of sem_op

	printf("Press enter to obtain the lock on the critical section\n");
	getchar();
	semOp.sem_op =-1; // negative mean decrement and -1 means P() operation
	status = semop(id, &semOp , 1);
	if(status<0){
		perror("Error while operating on semaphores");
	}

	readBytes = read(fd,&data,sizeof(data));

	if(readBytes<0){
		perror("Error while reading the file");
	}

	else if(readBytes ==0){
		data = 1;
	}
	else{
		data +=1;
		lseekoffset = lseek(fd,0,SEEK_SET);
		if(lseekoffset<0){
			perror("Error while setting the offset of the file");
		}
	}

	writeBytes = write(fd, &data, sizeof(data));
	if(writeBytes<0){
		perror("Error while writing to the ticket file");
	}

	printf("Your ticket number is %d. \n",data);
	printf("\n");
	printf("Press enter to exit the critical section");
	getchar();

	// making the critical section available by setting it to the abs value 
	semOp.sem_op = 1;//positive mean increment operation and +1 means V() operations
	status = semop(id,&semOp, 1);
	if(status<0){
		perror("Error while operating on semaphore");
	}
	return 0;
}

