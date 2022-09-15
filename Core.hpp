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

#define BUFSIZE 10024

//favicon.ico - запрос на иконку

class Core {
	private:
		Request *request;
		Processor *answer;

		struct sockaddr_in client;
		//char buf[BUFSIZE];
		socklen_t size;
		int maxFd = 0;
		fd_set active_set, read_set;
		fd_set active_write, write_set;
		int new_sock;

		int i, err, opt = 1;
		std::vector<Server *> vectorServers;
		std::vector<Server *>::iterator it;
		std::vector<Server *>::iterator end;

	public:

		Core(std::vector<Server *> vectorServers_) : vectorServers(vectorServers_) {
			end = vectorServers.end();
			
			FD_ZERO(&active_set);
			FD_ZERO(&active_write);

			for (it = vectorServers.begin(); it != end; ++it) {
				FD_SET((*it)->getFdSocket(), &active_set);
				std::cout << "\x1b[1;92m" << "> Listen Socked: " << (*it)->getFdSocket() << "\n" << "\x1b[0m";
				if ((*it)->getFdSocket()  >= maxFd) {
					maxFd = (*it)->getFdSocket() + 1;
				}
			}

			it = vectorServers.begin();
			
			while(1) {
				//memset(buf,0,BUFSIZE);
				read_set = active_set;
				//write_set = active_write;
				if (select(maxFd, &read_set, &write_set, 0, 0) < 0) {
					error("Error: Select socket failed");
				}
				for (i = 0; i < maxFd; i++) {
					std::cout << "Found active socket......." << i << "\n";
					if (FD_ISSET(i, &read_set)) {
						std::cout << "\x1b[1;96m" << "\n> Found Read socket___fd: " << i << "\n" << "\x1b[0m";
						if (getFDListenSocket(i) == 1) {
							size = sizeof(client);
							new_sock = accept((*it)->getFdSocket(), (struct sockaddr *)&client, &size);
							if (new_sock < 0) {
								error("Error: Accept socket failed");
							}
							std::cout << "\x1b[1;92m" << "> Create NEW Socket to Read: " << new_sock << "\n" << "\x1b[0m";
							FD_SET(new_sock, &active_set);
							//FD_SET(new_sock, &active_write);
							if (new_sock >= maxFd) {
								maxFd = new_sock + 1;
							}
						}
						if (readFromClient(i) < 0) {
							std::cout << "End of file, read_sock: " << i << "\n";
							close (i);
							FD_CLR(i, &active_set);
						}
						// else if (strstr(buf, "stop")) {
						// 	std::cout << "Stop\n";
						// 	close (i);
						// 	FD_CLR(i, &active_set);
						// }
						else {
							//std::cout << "ITS STEP TO WRITE BROWSER\n";
							writeToClient(i);
						}
					}
					if (FD_ISSET(i, &write_set)) {
						std::cout << "\x1b[1;96m" << "\n> Found Write socket___fd: " << i << "\n\n" << "\x1b[0m";
						if (getFDListenSocket(i) == 1) {
							size = sizeof(client);
							new_sock = accept((*it)->getFdSocket(), (struct sockaddr *)&client, &size);
							if (new_sock < 0) {
								error("Error: Accept socket failed");
							}
							std::cout << "\x1b[1;92m" << "> Create NEW Socket to Write: " << new_sock << "\n" << "\x1b[0m";
							FD_SET(new_sock, &active_set);
							if (new_sock >= maxFd) {
								maxFd = new_sock + 1;
							}
						}
						if (readFromClient(i) < 0) {
								std::cout << "End of file, write_sock: " << i << "\n";
								close (i);
								FD_CLR(i, &active_set);
						}
						// else if (strstr(buf, "stop")) {
						// 	std::cout << "Stop\n";
						// 	close (i);
						// 	FD_CLR(i, &active_set);
						// }
						// else {
						// 	writeToClient(i);
						// }
					}
				}
				std::cout << "\x1b[1;33m" << "> End of Found Circle: " << new_sock << "\n" << "\x1b[0m";
			}
			std::cout << "Exit\n";
		}

		~Core() {
			
		}

		int error (const char* err_type) {
			std::cerr << err_type << std::endl;
			exit(EXIT_FAILURE);
		}

		int readFromClient(int fd) { //// Сюда приходят данные от браузера GET POST и тд
			
			
			long	lenRequest;
			char buf[BUFSIZE];

			lenRequest = recv(fd, buf, BUFSIZE, 0);
			//request = new Request(buf);
			// if (strstr(buf, "\n")) {
			// 	std::cout << "\n------- END!!! -------\n\n";
			// }
			if (lenRequest > 0) {
				std::cout << "\x1b[1;31m" << "\n> HTTP from brauser___fd: " << fd << "\n\n" << "\x1b[0m";
				printf("%s\n", buf);
				std::cout << "\x1b[1;31m" << "> HTTP from brauser END___fd: " << fd << "\n" << "\x1b[0m";
				return (1);
			}
			else 
				return (-1);



			//-------------------------------------------
			// char buffer_1[10000] = {0};
			// ///////////// читаем http запрос от сервера
			// //size_t valread;
			// read(fd, buffer_1, 10000);
			// std::cout << "\n------- HTTP from brauser -------\n\n";
			// printf("%s\n", buffer_1); // вывели запрос в консоль
			// std::cout << "\n------- HTTP from brauser END -------\n\n";
			// // отправка файла клиенту (на браузер)
			// char buffer[1000] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";; // Content-Type - тип запрашиваемого файла
			// size_t readsize = strlen(buffer);
			// send(fd, buffer, (int)readsize, 0); // отправили заголовок
			// char filename[21] = "resources/post.html"; 
			// 	FILE *file = fopen(filename, "r"); // открываем файл для отправки
			// 	if (file == NULL) {
			// 		exit(-2);
			// 	}
			// 	while ((readsize = fread(buffer, sizeof(char), 1000, file)) != 0) {
			// 		send(fd, buffer, (int)readsize, 0);
			// 	} // читаем и отправляем файл по чуть-чуть
			// 	fclose(file);
			// 	//
			// 	//write(new_socket, msg.c_str(), msg.size());
			// 	std::cout << "------- Message send! --------\n";
			// 	close(fd);
			// return(-1);
			//-------------------------------------------
		}

		int writeToClient(int fd) {
			//answer = request->getProcessor(); //
			//char buffer[1000] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!"; 

			//size_t readsize = answer->getAnswer().length();
			//send(fd, answer->getAnswer().c_str(), (int)readsize, 0);
			char buffer[1000] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";; // Content-Type - тип запрашиваемого файла
			size_t readsize = strlen(buffer);
			send(fd, buffer, (int)readsize, 0); // отправили заголовок
			char filename[21] = "resources/post.html"; 
				FILE *file = fopen(filename, "r"); // открываем файл для отправки
				if (file == NULL) {
					exit(-2);
				}
				while ((readsize = fread(buffer, sizeof(char), 1000, file)) != 0) {
					send(fd, buffer, (int)readsize, 0);
				} // читаем и отправляем файл по чуть-чуть
				fclose(file);
			send(fd, buffer, strlen(buffer), 0);
			std::cout << "\x1b[1;92m" << "\n> Send Message To Browser!___fd: " << fd << "\n\n" << "\x1b[0m";
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
