/*Question -> Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls.
 * Name -> Samir Ahmed Ghouri Roll->MT2022100
 * */
#include<stdio.h>
#include<unistd.h>

int main()
{
	int max_size = 1000;
	char buff[max_size];
	int nread;
	nread = read(0 , buff ,max_size);
	write(1,buff, nread);
	return 0;
}

	
