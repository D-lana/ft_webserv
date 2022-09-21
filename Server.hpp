#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ADDRESS INADDR_ANY

class Server {
	
	private:
		int opt;
		int sock;
		struct sockaddr_in addr;

		int error (const char* err_type) {
			std::cerr << err_type << std::endl;
			exit(EXIT_FAILURE);
		}
	public:

			Server(int port) {
			opt = 1;
			sock = socket(PF_INET, SOCK_STREAM, 0);
			if (sock < 0) {
				error("Error: Creating socket failed");
			}
			setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
			setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, (char*)&opt, sizeof(opt)); // добавила, чтобы не вылетало видео 
			
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = htonl(ADDRESS);
			if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
				error("Error: Binding socket failed");
			}
			if (listen(sock, 32) < 0) {
				error("Error: Listening socket failed");
			}
		}

		~Server() {
			close(sock);
		}

		int getFdSocket() {
			return (sock);
		}

};

#endif