/* Questions->Write a program to copy file1 into file2 ($cp file1 file2)
 * Name -> Samir Ahmed Ghouri Roll->MT2022100
 * */
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{

	char buff;
	int fd1 ,fd2;
	
	fd1= open("file.txt",O_RDONLY);

	if(fd1<0){
		perror("program");
	}

	fd2 = creat("CopyFile.txt" , O_EXCL|S_IRWXU);

	while(read(fd1 , &buff , 1))
	{
		write(fd2 , &buff , 1);
	}

	printf("File Content copied successfully ");

	close(fd1);
	close(fd2);
}



