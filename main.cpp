#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Server.hpp"


#define PORT 8080

int main()
{
	Server *web_serv = new Server();
	web_serv->runServer();
}
