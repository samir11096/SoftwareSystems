/*Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv

Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>

int main()
{
	key_t key ;
	int id ;

	struct msqid_ds messageInfo;

	if(key=ftok(".",2)<0){
		perror("key program");
	}

	if(id = msgget(key , IPC_CREAT| IPC_EXCL|0666)<0)
	{
		perror("Message Queue Id Program");
	}
	else{
		printf("Message Queue Successfully Created\n");

		if(msgctl(id , IPC_STAT, &messageInfo)<0){
			perror("Message Info Program.");
		}
		else{
			printf("Access Permission : %d.\n",messageInfo.msg_perm.mode);
			printf("UID : %d.\n",messageInfo.msg_perm.uid);
			printf("GID : %d.\n",messageInfo.msg_perm.gid);
			printf("Time of Last Message Send : %ld.\n",messageInfo.msg_stime);
			printf("Time of Last Message Received : %ld.\n",messageInfo.msg_rtime);
			printf("Time of Last Change in Message : %ld.\n",messageInfo.msg_ctime);
			printf("Size of Queue : %ld.\n" ,messageInfo.__msg_cbytes);
			printf("Number of Message in Queue : %ld.\n",messageInfo.msg_qnum);
			printf("Maximum Number of Bytes Allowed : %ld.\n",messageInfo.msg_qbytes);
			printf("Pid of msgsnd : %d.\n",messageInfo.msg_lspid);
			printf("Pid of msgrcv : %d.\n",messageInfo.msg_lrpid);
		}

	
	}
	return 0;
}




