//Question-> Create a named pipe using mkfifo system call.
//Name -> Samir Ahmed Ghouri Roll->MT2022100
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	int fl;
	fl = mkfifo("fifo",0777);
	printf("Named Pipe Created\n");
}

