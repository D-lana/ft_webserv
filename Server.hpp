#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ServerPairs.hpp"

class Server {
	
	private:
		int opt;
		int sock;
		struct sockaddr_in addr;
		const ServerPairs& _serv;  //pveeta: предлагаю добавить

		int error (const char* err_type) {
			std::cerr << err_type << std::endl;
			exit(EXIT_FAILURE);
		}
	public:

		Server(int port); //pveeta: предлагаю удалить
		Server(const ServerPairs& serv); //pveeta: альтернатива
		~Server();
		int getFdSocket();
};

#endif