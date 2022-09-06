#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	char buff;
	int fd1 = open("file.txt" , O_RDONLY);

	if(fd1<0){
		perror("program");
	}

	int file_end = 0 ; 
	int index = 0;
	int read_bytes = 0;
	while(file_end == 0 ){
		read_bytes = read(fd1 , &buff, 1);
		if(buff == '\n'){
			printf("\n");
		}
		else{
			write(1 , &buff , read_bytes);
		}
		if(read_bytes ==0)
		{
			file_end =1;
		}
	}

	close(fd1);
	return 0;
}
