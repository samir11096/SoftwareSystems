#include<stdio.h>
#include<sched.h>
int main(){
	// doing it for FIFO , same will be for RR
	// for rest it will be 0
	int max_FIFO , min_FIFO;

	max_FIFO = sched_get_priority_max(SCHED_FIFO); // 99

	min_FIFO = sched_get_priority_min(SCHED_FIFO); // 1

	printf("The max priority of rt process using FIFO policy is %d .\n" , max_FIFO);

	printf("The min priority of rt process using FIFO policy is %d .\n" , min_FIFO);
	return 0;
}

