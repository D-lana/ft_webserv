#ifndef CORE_HPP
#define CORE_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>

#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"

#define PORT 8080
#define BUFSIZE 1024
#define ADDRESS INADDR_ANY

//favicon.ico - запрос на иконку

class Core {
	private:
		int sock_any;
		Request *request;
		Processor *answer;
		
		int new_sock;
		fd_set active_set, read_set, write_set;
		int maxFd = 0;

		int error (const char* err_type) {
			std::cerr << err_type << std::endl;
			exit(EXIT_FAILURE);
		}

		// struct sockaddr_in addr;
		socklen_t size;
		char buf[BUFSIZE];
		struct sockaddr_in client;

		std::vector<Server>::iterator it;
		std::vector<Server>::iterator end;

	public:
	Core (std::vector<Server> vectorServers) {
		FD_ZERO(&active_set);
		it = vectorServers.begin();
		end = vectorServers.end();
		while (it < end) {
			FD_SET(it->getFdSocket(), &active_set);
			it++;
		}
	}

	int runServer() {
		while(1) { // Проверим не появились ли данные в каком-либо сокете
			read_set = active_set;
			if (select(maxFd, &read_set, NULL, 0, 0) < 0) {
				error("Error: Select socket failed");
			}
			// данные появились, проверяем в каком фд есть запрос на чтение
			for (int fd = 0; fd < maxFd; fd++) {
				//std::cout << "New connection";
				if (FD_ISSET(fd, &read_set)) {
					sock_any = getAllSockets(fd);
					if (sock_any != 0) {
						// пришел запрос на новое соединение
						std::cout << "NEW SOCK - " << fd << "\n";
						size = sizeof(client);
						new_sock = accept(sock_any, (struct sockaddr *)&client, &size);
						if (new_sock < 0) {
							error("Error: Accept socket failed");
						}
						std::cout << "Server connect from host\n";
						//fcntl(new_sock, F_SETFL, O_NONBLOCK); /// НЕБЛОКИРУЮЩИЙ СОКЕТ 
						FD_SET(new_sock, &active_set);
						if (new_sock >= maxFd) {
							maxFd = new_sock + 1;
						}
						FD_SET(new_sock, &active_set);
						//fcntl(new_sock, F_SETFL, O_NONBLOCK); /// НЕБЛОКИРУЮЩИЙ СОКЕТ 
					}
					else {
						// пришли данные в существующем соединении
						if (readFromClient(fd, buf) < 0) {
							// ошибка или конец данных
							std::cout << "End of file\n";
							close (fd);
							//error("Error: readFromClient failed");
							FD_CLR(fd, &active_set);
						}
						else if (strstr(buf, "stop")) {
							std::cout << "Stop\n";
							close (fd);
							FD_CLR(fd, &active_set);
						}
						else {
							writeToClient(fd);
						}
					}
				}
			}
		}
		return (0);
	}

	~Core () {

	}

	int  getAllSockets(int fd) {
		int res = 0;
		while (it < end) {
			if (it->getFdSocket() == fd) {
				res = fd;
				break;
			}
			it++;
		}
		return(res);
	}

	int readFromClient(int fd_socket, char *buf) { //// Сюда приходят данные от браузера GET POST и тд 
		long	lenRequest;
		
		lenRequest = read(fd_socket, buf, BUFSIZE);
		request = new Request(buf);
		if (strstr(buf, "\n")) {
			std::cout << "\n------- END!!! -------\n\n";
		}
		else if (lenRequest > 0) {
			std::cout << "\n------- HTTP from brauser -------\n\n";
			printf("%s\n", buf);
			return (1);
		}
		else 
			return (-1);
		return (1);
	} 

	int writeToClient(int fd_socket) {
		answer = request->getProcessor(); //char buffer[1000] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!"; 
		size_t readsize = answer->getAnswer().length();
		send(fd_socket, answer->getAnswer().c_str(), (int)readsize, 0);
		return 0;
	}
};

#endif