//wait() makes the parentprocess to wait until the child process has terminated.

//status variable is an output paramter in which is encoded information about the way the child process terminated.

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int status;
	int id1 = fork();
	
	if(id1!=0){

		printf("Parent id %d Child id %d\n", getppid() ,getpid());
		int id2 = fork();
		if(id2!=0){
				
			int id3=fork();
			if(id3==0){
			printf("Parent id %d Child id %d\n", getppid() ,getpid());
			}
			else{
				printf("Waiting for %d child process to complete.\n",id2);
				waitpid(id2,&status,0);
			}
		}
		else{
			printf("Parent id %d Child id %d\n", getppid() ,getpid());
			sleep(10);
		}

	
	}
	else{
		printf("Parent id %d Child id%d\n", getppid() ,getpid());
	}
	return 0;
}

		




	
