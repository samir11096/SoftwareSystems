/*Write two programs so that both can communicate by FIFO -Use one way communication.
 * Name -> Samir Ahmed Ghouri
 * Roll -> MT2022100
 * */


#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main()
{
    int fd;
    char * myfifo = "myfifo";
    char buff[100];
    printf("Enter the string to be send : ");
    scanf("%s",buff);

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY);
    write(fd, buff, strlen(buff));
    close(fd);


    return 0;
}
