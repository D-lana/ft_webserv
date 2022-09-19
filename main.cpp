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
#include "Parser.hpp"

#define ADDRESS INADDR_ANY

int main(int argc, const char* argv[])
{
	if (argc != 2) {
        std::cerr << "No configuration file" << std::endl;
        return 0;
    }
	FILE* fp = fopen(argv[1], "r+");
	if (!fp) {
		std::cerr << "Unproper type of file" << std::endl;
		return 0;
	}
	std::fclose(fp);
	
	FtParser *parser = new FtParser(argv[1]);
	
	try {
		parser->parse(argv[1]);
	}
	catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
	
	/* код девочек

	int count_server = 2;
	int ports[3] = {8080, 8090};
	// config

	std::vector<Server*> vectorServers;
	for (int i = 0; i < count_server; i++) {
		Server *one_serv = new Server(ports[i]);
		std::cout << one_serv << "\n"; // проверка адреса ячейки
		vectorServers.push_back(one_serv);
		std::cout << vectorServers.back() << "\n"; // проверка адреса ячейки
	}

	Core main_core(vectorServers);
	std::cout << &main_core  << "\n"; // проверка адреса ячейки

	*/
}





