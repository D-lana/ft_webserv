#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define ADDRESS "127.0.0.1"

int main()
{
	int			sock = 0;
	long			valread;
	struct	sockaddr_in	serv_addr;

	char	*hello = new char[19];
    strcpy(hello,"Hello from client");
	char 			buffer[1024] = {0};
	//Creating of socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0))< 0)
	{
		printf("\n Error: In creating socket\n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
			
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr(ADDRESS);

	//Convert IPv4 and IPv6 addresses from text to binary
	if (inet_pton(AF_INET, ADDRESS, &serv_addr.sin_addr) <= 0)
	{
		printf("\n Error: Invalid Address/Address not supported\n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\n Error: Connection Failed\n");
		return -1;
	}
	send(sock, hello, strlen(hello), 0);
	printf("Message sent!\n");
	valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);
	return 0;
}


// Функция inet_ntoa () - вывести структуру sin_addr в виде строки IP (от сети до ascii). Такие как:
// printf("%s",inet_ntoa(mysock.sin_addr));

