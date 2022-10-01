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
		const ServerPairs& serv_pairs;

		int error (const char* err_type);

	public:

		Server(const ServerPairs& serv); 
		~Server();
		int getFdSocket();
		const std::string& getRootFromConfig() const;
		// const ServerPairs& getServerPairs() const;
};

#endif