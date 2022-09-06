/* Create a FIFO file by
 * b.mkfifo command
 *
 * Name ->Samir Ahmed Ghouri
 * Roll-> MT2022100
 * */

#include<stdio.h>
#include<sys/stat.h>

int main()
{
	if(mkfifo("myFIFO_2" , 0666)!=0){
		perror("mkfifo() program");
	}
	return 0;
}
