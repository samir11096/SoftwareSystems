/*Write a program to set (any one) system resource limit. Use setrlimit system call.
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
	struct rlimit limit;

	limit.rlim_cur= 100;
	limit.rlim_max=500;

	if(setrlimit(RLIMIT_FSIZE,&limit)<0){
		perror("SETLIMIT program");
	}
	struct rlimit mylimit;
	if(getrlimit(RLIMIT_FSIZE , &mylimit)<0){
		perror("GETLIMIT program");
	}
	if(mylimit.rlim_cur != RLIM_INFINITY){
	printf("The soft limit is %ld \n",mylimit.rlim_cur);
	}

	if(mylimit.rlim_max != RLIM_INFINITY){
	printf("The hard limit is %ld \n",mylimit.rlim_max);
	}
	return 0;

	return 0;
}
