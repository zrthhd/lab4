#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<sys/types.h>
//#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write


//Func for chat betwwen client and server
void func(int socket_desc)
{
	char buff[80];
	int n;

	//Infinite loop for chat
	for (;;) 
	{
		bzero(buff,80);

		//Read message from client & copy it in buffer
		read(socket_desc, buff, sizeof(buff));
		//Print buffer which contains client contents
		printf("From client %s\t To client : ", buff);
		bzero(buff, 80);
		n=0;
		//Copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n');
		//Send buffer ti client
		write(socket_desc, buff, sizeof(buff));
		//If message contains "Exit then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0)
		{
			printf("Server exit...\n");
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	int socket_desc;
//	,new_socket,c ;
	struct sockaddr_in server, client; //main socket variable
//	int fd; // socket file descriptor that will be used to identify the socket
	int conn; //connection file descriptor that will be used to distinguish client connections.
//	char *message; //array that will store the messages that are sent by the server
	int len;

	//Create socket
	socket_desc = socket (AF_INET , SOCK_STREAM , 0);
	if (socket_desc  == -1)
	{
		printf("Could not create socket...\n");
	}

	else
		printf("Socket successfully created...\n");
	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(8888); //define the port at which the server will listen for connections.
	server.sin_addr.s_addr = htonl(INADDR_ANY);
//	fd = socket(AF_INET, SOCK_STREAM, 0); //create a new socket and also return the identifier of the socket into fd.

	
	//Binding newly created socket to given IP and verification
	if(( bind(socket_desc, (struct sockaddr *)&server, sizeof(server))) != 0)
	{
		printf("Socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded...\n");
		

 	//Server is ready to listen and verification
	if((listen(socket_desc,5)) != 0)
	{
		printf("Listen failed...\n");
		exit(0);
	} 
	else
		printf("Server listening...\n");
	len = sizeof(client);


	//Accept data packet from client and verification
	conn = accept(socket_desc, (struct sockaddr *)&client, &len);
	if(conn < 0)
	{
		printf("Server accept failed...\n");
		exit(0);
	}
	else
		printf("Server accept the client...\n");

	//Func for chatting between client and server
	func(conn); 

	//After chatting close the socket
	close(socket_desc);
}
