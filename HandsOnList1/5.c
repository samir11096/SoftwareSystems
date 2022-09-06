/* Question->Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd.
Name -> Samir Ahmed Ghouri Roll-> MT2022100
*/
#include<stdio.h>
#include<fcntl.h>

int main()
{
	int count = 5;
	char arr[100];
	while(1)
	{
		if(count !=0){
			sprintf(arr, "file%d.txt" , count);
			int fd = creat(arr,S_IRWXU | O_RDWR );
			if(fd<0){
				perror("program");
			}
			else{
				printf("File %d created successfully." , count);
			}
			count--;
		}
	}
	return 0;
}


