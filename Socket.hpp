#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <netinet/in.h> //struct sockaddr_in

#define ADDRESS INADDR_ANY

class Socket {
	
	private:
		int                     fd;
		struct sockaddr_in		client_addr;
		int						listen_fd;
	
	public:

		Socket(int listen, int new_fd, struct sockaddr_in addr) {
				fd = new_fd;
				client_addr = addr;
				listen_fd = listen;
		}

		~Socket() {
			close(fd);
		}

		int getFd() {
			return (fd);
		}

		struct sockaddr_in getSockAddr() {
			return (client_addr);
		}
};

#endif