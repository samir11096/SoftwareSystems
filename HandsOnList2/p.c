#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>

int main()
{
	int sd,connection_fd;
	int bind_status;
	int listen_status;
	int client_size;

	struct sockaddr_in server , client;

	int readBytes , writeBytes;
	char data[200];

	sd = socket(AF_INET,SOCK_STREAM,0);

	if(sd<0){
		perror("Error while creating socket for server side");
	}

	printf("Server socket successfully created\n");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port = htons(8085);
	struct linger ls ;
	ls.l_onoff = 1;
	ls.l_linger = 0;
	if (setsockopt(sd, SOL_SOCKET,SO_LINGER, &ls, sizeof(ls)) == -1) {
    		perror("setsockopt");
	}
	

	bind_status = bind(sd,(void*)&server, sizeof(server));

	if(bind_status<0){
		perror("Error in binding address to socket");
	}
	printf("Successfully binded the IP address with the socket\n");

	listen_status = listen(sd,1);

	if(listen_status<0){
		perror("Error while listening for connections");
	}

	printf("Now listening for connection for sockets\n");

	client_size = (int)sizeof(client);
	connection_fd = accept(sd, (void *)&client , &client_size);
	if(connection_fd<0){
		perror("Error while accepting client connection");
	}
	else{
		readBytes = read(connection_fd , data,100);
		if(readBytes<0){
			perror("Error while reading from client");
		}
		else{
			printf("Data received from client is %s\n",data);
		}
		writeBytes = write(connection_fd , "Hi , I am the server!\n",20);
		
		if(writeBytes<0){
			perror("Error while sending data to client");
		}

		else{
			printf("Data sent to client successfully\n");
		}
	}

	close(connection_fd);
	close(sd);
	return 0;
}
	


