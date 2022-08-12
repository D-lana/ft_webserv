#ifndef SERVER_HPP
#define SERVER_HPP

// # include <iostream>
// # include <exception>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>

#define PORT 8080

class Server {
	
	private:
		
		int 	server_fd;
		int 	new_socket;
		long	valread;
		struct 	sockaddr_in address;
		int		addrlen = sizeof(address);
		std::string msg;

	public:

		Server() {
			msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!";
			if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
			{
				std::cerr << "Error: Creating socket failed" << std::endl;
				exit(EXIT_FAILURE);	
			}
			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons(PORT);
			memset(address.sin_zero, '\0', sizeof address.sin_zero);
			if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
			{
				std::cerr << "Error: Binding socket failed" << std::endl;
				exit(EXIT_FAILURE);
			}
			if (listen(server_fd, 10) < 0)
			{
				std::cerr << "Error: Listening socket failed" << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		~Server() {
			close(server_fd);
		}

		// class IndexException : public std::exception
		// {
		// 	public:
		// 		const char* what() const throw();
		// };
		// Server(const Server &copy);
		// Server &operator =(const Server &copy);

		int runServer() {			
			while (1)
			{
				std::cout << "\n------- Waiting for new connection -------\n\n";
				if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
				{
					std::cerr << "Error: Listening socket failed" << std::endl;
					exit(EXIT_FAILURE);
				}
				char buffer[1000] = {0};
				///////////// !!!!!
				valread = read(new_socket, buffer, 1000);
				printf("%s\n", buffer);
				write(new_socket, msg.c_str(), msg.size());
				std::cout << "------- Hello message sent --------\n";
				close(new_socket);
			}
			return 0;
		}
};

#endif 
