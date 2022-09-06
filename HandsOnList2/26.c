/* Write a program to send messages to the message queue
 *
 * Name->Samir Ahmed Ghouri
 * Roll -> MT2022100
 * */

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
	printf("Enter the character to be send using Message Queue: ");
	scanf("%c",&msgData.mtext[0]);

	//msgData.mtext[0] = 'S';

	if(msgsnd(id , &msgData , sizeof(msgData) , 0)<0){
		perror("Message Sending Error Program ");
	}
	else{
		printf("Message Sent Successfully!!\n");
	}
	return 0;
}










	


