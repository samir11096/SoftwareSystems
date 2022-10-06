#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/ip.h>

int main()
{
	int sd;
	int status;

	struct sockaddr_in server;// using struct sockaddr_in beacuse of IPV4 protocol else for unix use struct sockaddr_un
	
	int readBytes , writeBytes;
	char data[200];

	sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
	{
		perror("Error while creating a socket");
	}

	printf("Client socket successfully created!!\n");

	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8085);
	server.sin_family = AF_INET; // cause we are using ipv4 family also struct address_in else we could have use struct address_un

	int connection_status = connect(sd,(void*)&server,sizeof(server));
	printf("%d\n",connection_status);

	if(connection_status <0){
		perror("Error while connecting with server");
	}
	printf("Client successfully connected to server\n");

	writeBytes = write(sd , "Hi, I am a client", 17);
	if(writeBytes< 0){
		perror("Error while writing to the server");
	}
	else{
		printf("Data sent to the server!\n");
	}

	readBytes = read(sd , data,100);
	if(readBytes<0){
		perror("Error while reading data from server");
	}
	else{
		printf("The data from server is %s \n",data);
	}

	close(sd);
	return 0;
}

