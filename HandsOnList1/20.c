#include<stdio.h>
#include<unistd.h>
#include<sys/resource.h>
int main()
{
	int pr = getpriority(PRIO_PROCESS , 0);
	printf("The prioriy of the current process is %d.\n",pr);
	
	// using nice command to change the priority
	if(nice(10)<0){
		perror("program");
	}
	pr = getpriority(PRIO_PROCESS,0);
	printf("The priority of the current process is %d.\n",pr);
	return 0;
}
