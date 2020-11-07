#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>

int main(int argc , char *argv[])
{
	int socket_desc, fd;
	struct sockaddr_in server; 
        char *message = malloc (100), server_reply[6000];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}



	fd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	inet_pton(AF_INET, "192.168.0.135", &server.sin_addr); //This binds the client to localhost
	connect(fd, (struct sockaddr *)&server, sizeof(server)); //This connects the client to the server.

	

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected \n");



	//Send some data
	while(1)
	{
    		printf("Enter a message: ");
    		fgets(message, 100, stdin);
    		send(fd, message, strlen(message), 0);
    		//extra breaking condition can be added here (to terminate the while loop)
		break;


	}

	

	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");


	//Receive a reply from the server
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	puts("Reply received\n");
	puts(server_reply);




	return 0;
}

