/*Write two programs so that both can communicate by FIFO -Use two way communications.
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 * */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>

int main()
{
    	int fd;
    	char * myfifo = "myfifo1";
    	char receive[100];

    	fd = open(myfifo, O_RDONLY);
    	read(fd, receive, 100);
    	printf("Received from sender: %s\n", receive);
	close(fd);

	myfifo = "myfifo2";
    	char send[100];
    	printf("Enter the string to be send to sender : ");
    	scanf("%s",send);

    	/* create the FIFO (named pipe) */
   	mkfifo(myfifo, 0666);

    	/* write "Hi" to the FIFO */
    	fd = open(myfifo, O_WRONLY);
    	write(fd, send, strlen(send));
    	close(fd);

	return 0;
}

