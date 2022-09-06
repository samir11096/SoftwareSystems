//Question-> Create a soflink using symlink system call.
//Name -> Samir Ahmed Ghouri Roll-> MT2022100
#include<stdio.h>
#include<unistd.h>
int main()
{
	symlink("source" , "symlink");
	perror("link ret: ");
	return 0;
}
