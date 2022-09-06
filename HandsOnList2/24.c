/*Write a program to create a message queue and print the key and message queue id.
 * 
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 * */

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>


int main()
{
	key_t key;
	int id;
	if( key = ftok(".",5)<0){
		perror("key program");
	}

	if(id = msgget(key , IPC_CREAT | IPC_EXCL |0666)<0)
	{
		perror("id program");
	}
	else{
		printf("Message Queue successfully created\n");
		printf("Key is : %d\n",key);
		printf("Id is : %d\n",id);

	}
	return 0;
}


	





