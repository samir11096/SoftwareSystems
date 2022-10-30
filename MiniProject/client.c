#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>

void connection_handler(int connectionFD);

int main()
{
    int socketFD , bindStatus ,connectionStatus;
    struct sockaddr_in serverAddress;

    socketFD = socket(AF_INET,SOCK_STREAM,0);
    if(socketFD<0){
        perror("Error while creating server socket!");
        _exit(0);
    }

    printf("Socket Created Successfully!!\n");

    serverAddress.sin_family =AF_INET;
    serverAddress.sin_addr.s_addr=INADDR_ANY;
    serverAddress.sin_port=htons(8800);

    connectionStatus = connect(socketFD , (struct sockaddr *)&serverAddress,sizeof(serverAddress));
    if(connectionStatus<0){
        perror("Error while connecting to server!");
        close(socketFD);
        _exit(0);
    }

    connection_handler(socketFD);
    close(socketFD);
    return 0;

}

void connection_handler(int socketFD){
    printf("In the client handler\n");

    int readBytes , writeBytes;
    char readBuffer[1000] , writeBuffer[1000];

    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    readBytes = read(socketFD,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading from the server");
        return ;
    }
    printf("%s\n",readBuffer);

    while(readBytes>0){

        bzero(readBuffer,sizeof(readBuffer));
        bzero(writeBuffer,sizeof(writeBuffer));
        scanf("%s",writeBuffer);
        writeBytes = write(socketFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes <0){
            perror("Error while sending client input to server!");
            return;
        }

        readBytes = read(socketFD,readBuffer,sizeof(readBuffer));
        if(readBytes<0){
            perror("Error while reading from the server");
            return ;
        }

        if(strcmp(readBuffer,"Wrong Input!!")==0){
            printf(".\n");
        }

        printf("%s\n",readBuffer);
         
    }


}