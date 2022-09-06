/*Write a program to receive messages from the message queue.
a. with 0 as a flag

Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/

#include<stdio.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<unistd.h>

int main()
{
	key_t key;
	int id ;

	struct msgbuf{
		long mtype;
		char mtext[1];
	}msgData;

	if(key=ftok(".",2)<0){
		perror("Key Program");
	}

	if(id=msgget(key , IPC_CREAT|IPC_EXCL|0666)<0){
		perror("Create Message Queue Program");
	}

	msgData.mtype = 1;


	if(msgrcv(id , &msgData , sizeof(msgData) ,msgData.mtype, 0)<0){
		perror("Message Sending Error Program ");
	}
	else{
		printf("Received Message : %c.\n",msgData.mtext[0]);
	}
	return 0;
}

