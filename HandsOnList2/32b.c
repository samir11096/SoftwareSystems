/* Write a program to implement semaphore to protect any critical section.
b. protect shared memory from concurrent write access

Name -> Samir Ahmed Ghouri

Roll -> MT2022100

*/

#include <sys/ipc.h>   
#include <sys/sem.h>  
#include<sys/shm.h>
#include <sys/types.h>
#include <unistd.h>  
#include <stdio.h>   

int main()
{
	int fd;
	int status;

	
	//defining the value of sempahore
	union semun {
		int val;
	} semSet;

	//creating a key for semaphore set
	key_t key = ftok(".",312);
	
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

	/*creating a shared memory */

	//creating a unique key
	int shmkey = ftok(".",124);
	if(shmkey<0){
		perror("Error while creating a key for shared memory");
	}

	//getting the id for the created shared memory 
	int shmid = shmget(shmkey , 20,IPC_CREAT|0700);
	if(shmid<0){
		perror("Error while creating shared memory");
	}

	//attaching the shared memory to a process address space
	char* shmptr = shmat(shmid , (void *)0 , 0); // the last 0 means we are giving read wirte priviledges 
	
	if(shmptr<0){
		perror("Error while attaching the shared memory");
	}

	
	//sembuf contains sem_num , sem_op, sem_flg
	struct sembuf semOp;
	semOp.sem_num = 0; // semaphore number in the set
	semOp.sem_flg = 0; // default behaviour of sem_op

	printf("Press enter to obtain the lock on the critical section\n");
	getchar();
	semOp.sem_op =-1;
	status = semop(id, &semOp , 1);
	if(status<0){
		perror("Error while operating on semaphores");
	}
	
	printf("Enter a string to write to the critical section :");
	scanf("%s",shmptr);
	getchar();

	printf("Successfully Written!!\n");

	printf("Press Enter to exit the critical section\n");
	getchar();

	// making the critical section available by setting it to the abs value 
	semOp.sem_op = 1;
	status = semop(id,&semOp, 1);
	if(status<0){
		perror("Error while operating on semaphore");
	}
	return 0;
}

	


