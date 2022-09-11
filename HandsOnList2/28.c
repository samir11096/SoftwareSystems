/*Write a program to change the exiting message queue permission. (use msqid_ds structure)
 *
 * Name -> Samir Ahmed Ghouri 
 * Roll -> MT2022100
 *
 * */

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>

int main()
{
	key_t key ;
	int id ;

	struct msqid_ds messageInfo;
	key = ftok(".",3);

	if(key<0){
		perror("key program");
	}
	printf("%d\n",key);
	
	id= msgget(key,IPC_CREAT|0666);
	if(id <0)
	{
		perror("Message Queue Id Program");
	}
	printf("%d\n",id);

	if(msgctl(id , IPC_STAT, &messageInfo)<0){
		perror("Message Info Program.");
	}
	
	printf("Access Permission : %d.\n",messageInfo.msg_perm.mode);

	messageInfo.msg_perm.mode = 0777;

	if(msgctl(id , IPC_SET, &messageInfo)<0){
		perror("Message Info Program.");
	}
	printf("New Access Permission : %d.\n",messageInfo.msg_perm.mode);
	return 0;
}
	



		

