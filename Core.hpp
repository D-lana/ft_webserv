#ifndef CORE_HPP
# define CORE_HPP

// #include <sys/socket.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <netinet/in.h>
// #include <iostream>
// #include <stdio.h>
// #include <string.h>
// #include <sys/types.h>
// #include <netdb.h>
// #include <fcntl.h>
// #include <poll.h>
// #include <vector>
// //#include <map>
// #include <list>

// #include <algorithm>

// #include "Server.hpp"
// #include "Request.hpp"
// #include "Response.hpp"
// #include "Http.hpp"
// //#include "CGI.hpp"
#include "Library.hpp"

#define BUFSIZE 1024

typedef struct s_Client 
{
	int						listen_sock;
	int						sock;
	struct sockaddr_in		client_addr;
	socklen_t				size_client_addr;
	int						ready_to_send;
	int 					send_end;

}							t_Client;

class Core {
	private:
		Http					*http;
		ServerPairs              *null_ptr1;
		// добавить переменную на keep_alive/keep_stop - обрубить соединение клиента или нет

		fd_set					active_read, read_set;
		fd_set					active_write, write_set;
		int						maxFd;

		std::list<t_Client>				list_clients;
		std::list<t_Client>::iterator	it_clients;
		
		int						new_sock;
		struct sockaddr_in		client_addr;
		socklen_t				size_client_addr;

		std::vector<Server *>	vectorServers;
		int						count_servers;
		
		int						close_connection;

		std::string				root;


	public:

		Core(std::vector<Server *> vectorServers_);
		~Core() {};
		void run();
		int createNewSocket();

		int error (const char* err_type);

		int writeToClient(int fd);
		int readFromClient(int fd);
		
		int getFDListenSocket(int fd);
		const std::string& getRootFromConfig(int fd) const;
		const ServerPairs& getServerPairs(int fd);
};

#endif