#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>
#include <iterator>
//#include "Server.hpp"
#include "Core.hpp"


#define PORT 8080


struct Config {
        char *listening;
        u_short port;
        in_addr_t host;
		// Эти даннные будут из конфига
};

int main()
{
	// ------Эти даннные будут из конфига
	Config conf1;
	conf1.port = 8080;
	Config conf2;
	conf2.port = 7070;
	int count_serv = 2;
	// ------Эти даннные будут из конфига
	std::list<Config> listConfig;
	listConfig.push_back(conf1);
	listConfig.push_back(conf2);
	std::list<Config>::iterator it = listConfig.begin();
	// ------Эти даннные будут из конфига
	
	std::vector<Server> vectorServers;

	for (int i; i < count_serv; i++) {
		Server *one_serv = new Server();
		vectorServers.push_back(*one_serv);
	}
	Core *coreWebSerwer = new Core(vectorServers);
	coreWebSerwer->runServer();
}
