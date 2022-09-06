/* Question -> Write a program to open an existing file with read write mode. Try O_EXCL flag also
 * Name -> Samir Ahmed Ghouri Roll->MT2022100
 * */
#include<stdio.h>
#include<fcntl.h>

int main()
{
	int fd = creat("a.txt" , O_RDWR | O_EXCL);
	if(fd==-1){
		perror("Program");
	}
	else{
		printf("File created successfully");
	}
	return 0 ; 
}
