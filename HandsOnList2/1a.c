/* Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
a. ITIMER_REAL

Name -> Samir Ahmed Ghouri 
Roll -> MT2022100
*/

#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>

int main()
{
	struct itimerval it;
	int choice;
	printf("Choose 1 -> interval time 10sec  and 2 -> interval time 10micro sec.: ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			it.it_value.tv_sec = 10;
			it.it_value.tv_usec =0;
			it.it_interval.tv_sec = 0;
			it.it_interval.tv_usec = 0;
			break;
		case 2:
			it.it_value.tv_sec = 0;
			it.it_value.tv_usec =10;
			it.it_interval.tv_sec = 0;
			it.it_interval.tv_usec = 0;
			break;
		}

	if(setitimer(ITIMER_REAL,&it,0)<0)
	{
		perror("ITIMER Error Program");
	}
	sleep(20);
	return 0;
}



