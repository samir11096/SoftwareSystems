/*Create a FIFO file by
a. mknod command

Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
	if(mknod("myFIFO", S_IFIFO|0666,0 )!=0){
		perror("mknod() program");
	}
	return 0;
}
