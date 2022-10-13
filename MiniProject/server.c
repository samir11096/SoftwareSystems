
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<strings.h>


#include "./constants/constants.h"
#include "./handler/admin.h"
#include "./handler/customer.h"

//handler decleration

void connection_handler(int connectionFD);

int main()
{
	int socketFD , bindStatus ,listenStatus,connectionFD;
	struct sockaddr_in serverAddress , clientAddress;
	int client_size;


	//creating socket for server
	
	socketFD = socket(AF_INET , SOCK_STREAM,0);
	if(socketFD<0){
		perror("Error while creating server socket");
		_exit(0);
	}
	printf("Server socket created successfully!!\n");

	
	//bind the socket to all avaliable  interface i.e. any IPv4 address can connect to server.
	serverAddress.sin_addr.s_addr = INADDR_ANY; 
	serverAddress.sin_port = htons(8800);
	serverAddress.sin_family = AF_INET; //	IPv4

	bindStatus = bind(socketFD , (struct sockaddr *) &serverAddress,sizeof(serverAddress));

	if(bindStatus<0){
		perror("Error while binding socket ");
		close(socketFD);
		_exit(0);
	}

	printf("Server socket binded successfully!!\n");
	
	listenStatus = listen(socketFD, 4);//server can listen to 4 client

	if(listenStatus<0){
		perror("Error while listening for clients");
		close(socketFD);
		_exit(0);
	}

	printf("Listening for clients!!\n");


	while(1)
	{
		client_size = (int)sizeof(clientAddress);
		connectionFD = accept(socketFD , (struct sockaddr*)&clientAddress , &client_size);
		if(connectionFD<0){
			perror("Error while connecting to client!");
			close(socketFD);
			_exit(0);
		}
		else{
			if(fork()==0){
				printf("Client Successfully connected to server!!\n");
				connection_handler(connectionFD);
				close(connectionFD);
			}
		}
	}
	close(socketFD);
	return 0 ;
}

//defining the connection handler

void connection_handler(int connectionFD){
	printf("In the server handler\n");
	
	char readBuffer[500] , writeBuffer[500];
	int readBytes , writeBytes;
	int choice;

	writeBytes = write(connectionFD,INITIAL_DAILOGUE,strlen(INITIAL_DAILOGUE));
	if(writeBytes<0){
		perror("Error while sending the first screen");
	}
	else{
		//zeroing a byte string 
		bzero(readBuffer , sizeof(readBuffer));
		readBytes = read(connectionFD,readBuffer , sizeof(readBuffer));
		if(readBytes<0){
			perror("Error while reading choice of client ");
		}
		else{
			choice = atoi(readBuffer);//convert character string to interger
			switch(choice){
				case 1:
					//admin
					admin_handler(connectionFD);	
					break;
				case 2:
					//customer
					//customer_handler(connectionFD);
					customer_handle(connectionFD);
					break;
				default:
					//wrong option 
					break;
			}
		}

	}
}






	



	

