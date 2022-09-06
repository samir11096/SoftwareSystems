#include<stdio.h>
#include<unistd.h>
#include<sched.h>
int main()
{
	int id = getpid();
	int policy =sched_getscheduler(id); // can also use 0 for current process
	switch(policy){
		case SCHED_OTHER:
			printf("The process policy is SCHED_OTHER.\n");
			break;

		case SCHED_RR:
			printf("The process policy is SCHED_RR.\n");
			break;

		case SCHED_FIFO:
			printf("The process policy is SCHED_FIFO.\n");
			break;
	}
	
	struct sched_param sp ;
	sp.sched_priority = 1;
	// run the program with sudo or root access
	if(sched_setscheduler(getpid() , SCHED_FIFO, &sp)<0){
		perror("program");
	}
	
	policy = sched_getscheduler(id);

	switch(policy){
		case SCHED_OTHER:
			printf("The process policy is SCHED_OTHER.\n");
			break;

		case SCHED_RR:
			printf("The process policy is SCHED_RR.\n");
			break;

		case SCHED_FIFO:
			printf("The process policy is SCHED_FIFO.\n");
			break;
	}
	return 0;
}
