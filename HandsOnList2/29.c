/*Write a program to remove the message queue.
 * Name->Samir Ahmed Ghouri
 * Roll-> MT2022100
 * */

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>

int main()
{
	key_t key;
	int id;

	struct msqid_ds messageInfo;

	key = ftok(".",9);

	if(key<0){
		perror("key program");
	}
	//creating the message queue

	id= msgget(key,IPC_CREAT|0666);

	if(id <0)
	{
		perror("Message Queue Id Program");
	}

	printf("Message queue with key %d and id %d is created.\n",key , id);
	
	//deleteting the message queue using IPC_RMID and third argument as NULL as mention in man page
	if(msgctl(id , IPC_RMID,NULL )<0){
		perror("Message Info Program.");
	}

	printf("Message queue DELETED successfully.\n");
	return 0;

}



