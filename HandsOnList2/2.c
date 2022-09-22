/*Write a program to print the system resource limits. Use getrlimit system call.
 * 
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 *
 * */

#include<stdio.h>
#include<sys/time.h>
#include<sys/resource.h>

int main()
{
	struct rlimit mylimit;

	if(getrlimit(RLIMIT_FSIZE, &mylimit)<0)
	{
		perror("GETLIMIT Program");
	}
	if(mylimit.rlim_cur==RLIM_INFINITY){
		printf("The soft limit is Unlimited\n");
	}
	if(mylimit.rlim_max == RLIM_INFINITY){
		printf("The hard limit is Unlimited\n");
	}
	if(mylimit.rlim_cur != RLIM_INFINITY){
	printf("The soft limit is %ld \n",mylimit.rlim_cur);
	}

	if(mylimit.rlim_max != RLIM_INFINITY){
	printf("The hard limit is %ld \n",mylimit.rlim_max);
	}
	return 0;
}
