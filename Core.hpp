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

#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Http.hpp"

#define BUFSIZE 1024

//favicon.ico - запрос на иконку

class Core {
	private:
		Http *http;
		// Request *request; // убрать?
		// Processor *answer;

		struct sockaddr_in client;
		char buf[BUFSIZE];
		socklen_t size;
		int maxFd = 0;
		fd_set active_set, read_set;
		int new_sock;

		int i, err, opt = 1;
		std::vector<Server *> vectorServers;
		std::vector<Server *>::iterator it;
		std::vector<Server *>::iterator end;

	public:

		Core(std::vector<Server *> vectorServers_) : vectorServers(vectorServers_) {
			end = vectorServers.end();
			
			FD_ZERO(&active_set);

			for (it = vectorServers.begin(); it != end; ++it) {
				FD_SET((*it)->getFdSocket(), &active_set);
				std::cout << "LISTEN SOCK - " << (*it)->getFdSocket() << "\n";
				if ((*it)->getFdSocket()  >= maxFd) {
					maxFd = (*it)->getFdSocket() + 1;
				}
			}

			it = vectorServers.begin();
			
			while(1) {
				memset(buf,0,BUFSIZE);
				read_set = active_set;
				if (select(maxFd, &read_set, NULL, 0, 0) < 0) {
					error("Error: Select socket failed");
				}
				for (i = 0; i < maxFd; i++) {
				
					if (FD_ISSET(i, &read_set)) {
						if (getFDListenSocket(i) == 1) {
							std::cout << "NEW SOCK - " << i << "\n";
							size = sizeof(client);
							new_sock = accept((*it)->getFdSocket(), (struct sockaddr *)&client, &size);
							if (new_sock < 0) {
								error("Error: Accept socket failed");
							}
							FD_SET(new_sock, &active_set);
							if (new_sock >= maxFd) {
								maxFd = new_sock + 1;
							}
						}
						else {
							if (readFromClient(i, buf) < 0) {
								std::cout << "End of file\n";
								close (i);
								FD_CLR(i, &active_set);
							}
							else if (strstr(buf, "stop")) {
								std::cout << "Stop\n";
								close (i);
								FD_CLR(i, &active_set);
							}
							else {
								writeToClient(i);
							}
						}
					}
				}

			}
			std::cout << "Exit\n";
		}

		~Core() {
			
		}

		int error (const char* err_type) {
			std::cerr << err_type << std::endl;
			exit(EXIT_FAILURE);
		}

		int readFromClient(int fd, char *buf) { //// Сюда приходят данные от браузера GET POST и тд
			long	lenRequest;
		
			lenRequest = read(fd, buf, BUFSIZE);
			// std::cout << "buf |" << buf << "|" << std::endl;
			std::string buffer(buf); // добавила obeedril
			// std::cout << "buffer_core |" << buffer << "|" << std::endl;
			
			// http = new Http(fd, buffer); // добавила obeedril

			// request = new Request(std::string(buf));
			if (strstr(buf, "\n")) {
				std::cout << "\n------- END!!! -------\n\n";
			}
			if (lenRequest > 0) {
				std::cout << "\n------- HTTP from brauser -------\n\n";
				printf("%s\n", buf);
				http = new Http(fd, buffer); // добавила obeedril
				return (1);
			}
			else 
				return (-1);
		}

		int writeToClient(int fd) {
			std::cout << "\n------- writeToClient!!! -------\n\n";
			//answer = request->getProcessor(); //char buffer[1000] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!"; 
			//size_t readsize = answer->getAnswer().length();
			size_t readsize = http->getPartAnswer().length();
			send(fd, http->getPartAnswer().c_str(), (int)readsize, 0);
			// send(fd, answer->getAnswer().c_str(), (int)readsize, 0);
			return (0);
		}

		int getFDListenSocket(int fd) {
			for (it = vectorServers.begin(); it != end; ++it) {
				if ((*it)->getFdSocket() == fd) {
					return(1);
				}
			}
			return(0);
		}
};

#endif