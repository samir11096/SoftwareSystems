/*Write two programs so that both can communicate by FIFO -Use two way communications.
 *
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
	char * myfifo = "myfifo1";
    	int fd;
    	char send[100];
    	printf("Enter the string to be send to receiver : ");
    	scanf("%s",send);

    	/* create the FIFO (named pipe) */
   	mkfifo(myfifo, 0666);

    	/* write "Hi" to the FIFO */
    	fd = open(myfifo, O_WRONLY);
    	write(fd, send, strlen(send));
    	close(fd);


    	myfifo = "myfifo2";
    	char receive[100];

    	fd = open(myfifo, O_RDONLY);
    	read(fd, receive, 100);
    	printf("Received from receiver: %s\n", receive);
	close(fd);

	

	return 0;
}

	

		


