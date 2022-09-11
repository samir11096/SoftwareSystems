/*Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory

Name -> Samir Ahmed Ghouri
Roll -> MT2022100

*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>

int main()
{
	key_t key;
	int id;
	size_t size = 20;

	char * shmaddr ;

	key =ftok(".",30);

	if(key<0){
		perror("key program");
	}
	
	//creating the shared memory 
	id = shmget(key , size , IPC_CREAT|0666);
	printf("Shared Memory created successfully.\n");

	if(id<0){
		perror("ID program");
	}
	
	//attaching the shared memory to the current process in read only mode
	
	shmaddr = (char *)shmat(id , (void * )NULL , SHM_RDONLY);
	printf("Shared Memory attached to the current process successfully.\n");

	//writing to the shared memory will give segmentation fault

	/*
	printf("Write Data to shared memory : ");
	gets(shmaddr);

	printf("Data written in memory: %s\n",shmaddr);
	*/ 

	
	//Detaching the pointer from shared memory
	printf("Detaching the pointer from shared memory.\n");
	shmdt(shmaddr);
		

	//Removing the shared memory
	shmctl(id,IPC_RMID,NULL);
	printf("Shared Memory removed successfully.\n");
	

	return 0;
}




