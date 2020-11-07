#include<stdio.h>
#include<stdlib.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write



int main(int argc, char *argv[])
{
	int socket_desc,new_socket,c ;
	struct sockaddr_in server, client; //main socket variable
	int fd; // socket file descriptor that will be used to identify the socket
	int conn; //connection file descriptor that will be used to distinguish client connections.
	char *message; //array that will store the messages that are sent by the server


	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}


	server.sin_family = AF_INET;
	server.sin_port = htons(8888); //define the port at which the server will listen for connections.
	server.sin_addr.s_addr = INADDR_ANY;
	fd = socket(AF_INET, SOCK_STREAM, 0); //create a new socket and also return the identifier of the socket into fd.

	
	// To handle errors, you can add an if condition that checks whether fd is greater than 0. If it isn't, prompt an error
	bind(fd, (struct sockaddr *)&server, sizeof(server)); //assigns the address specified by serv to the socket
	listen(fd,5); //listen for client connections. Maximum 5 connections will be permitted.


	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("Connection accepted");


		//start handling the connections.
		while(conn = accept(fd, (struct sockaddr *)NULL, NULL)) 
		{
    			int pid;
    			if((pid = fork()) == 0) 
	
        

			while (recv(conn, message, 100, 0)>0)
			{
            			printf("Message Received: %s\n", message);
           	 		//extra breaking condition can be added here (to terminate the child process)            
            			message = "";
			}
        	}
	}
		
	

	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	
	return 0;
}

