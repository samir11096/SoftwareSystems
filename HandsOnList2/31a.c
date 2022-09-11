/*Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore

Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>

int main()
{
	union semun{
		int val;
	};

	union semun arg;

	key_t key= ftok(".",12);
	if(key<0){
		perror("key program");
	}

	int id = semget(key , 1 , IPC_CREAT|0666);

	if(id<0)
	{
		perror("id program");
	}
	
	//setting the value of the semaphore as 1 for binary semaphore
	arg.val = 1;

	//initialising the semaphore
	
	if(semctl(id , 0,SETVAL ,arg)<0){
		perror("control operation Program");
	}
	printf("Binary Semaphore Successfully Created.\n");

	return 0;
}





