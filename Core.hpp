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
//#include <map>
#include <list>

#include <algorithm>

#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Http.hpp"
#include "Socket.hpp"
//#include "CGI.hpp"

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
		// добавить переменную на keep_alive/keep_stop - обрубить соединение клиента или нет

		fd_set					active_read, read_set;
		fd_set					active_write, write_set;
		int						maxFd;

		//std::map<int, t_Client>		listClients;
		std::list<t_Client>				list_clients;
		std::list<t_Client>::iterator	it_clients;
		
		int						new_sock;
		struct sockaddr_in		client_addr;
		socklen_t				size_client_addr;

		std::vector<Server *>	vectorServers;
		int						count_servers;
		
		int						close_connection;

	public:

		Core(std::vector<Server *> vectorServers_) : vectorServers(vectorServers_) {
			http = new Http(); // добавила obeedril
			maxFd = 0;
			count_servers = vectorServers.size();

			FD_ZERO(&active_read);
			FD_ZERO(&active_write);
			std::cout << count_servers  << "\n";

			for (int i = 0; i < count_servers; ++i) {
				FD_SET(vectorServers[i]->getFdSocket(), &active_read);
				std::cout << "\x1b[1;92m" << "> Listen Socked: " << vectorServers[i]->getFdSocket() << "\n" << "\x1b[0m";
				if (vectorServers[i]->getFdSocket()  >= maxFd) {
					maxFd = vectorServers[i]->getFdSocket() + 1;
				}
			}

			while(1) {
				read_set = active_read;
				write_set = active_write;
				//std::cout << "\x1b[1;31m" << "> Select block " << "\n" << "\x1b[0m";
				if (select(maxFd, &read_set, &write_set, 0, 0) < 0) {
					continue;
					//error("Error: Select socket failed");
				}
				createNewSocket();
				for (it_clients = list_clients.begin(); it_clients != list_clients.end(); ++it_clients) {
					//std::cout << "\x1b[1;33m" << "\n> Next sock: " << it_clients->sock << "\n\n" << "\x1b[0m";
					if (FD_ISSET(it_clients->sock, &read_set) && it_clients->ready_to_send == -1) {
							std::cout << "\x1b[1;96m" << "\n> Found Read socket fd: " << it_clients->sock << "\n\n" << "\x1b[0m";
							close_connection = readFromClient(it_clients->sock);
							if (close_connection == 0) {
								std::cout << "\x1b[1;33m" << "\n> Close socked: " << it_clients->sock << "\n\n" << "\x1b[0m";
								close (it_clients->sock);
								FD_CLR(it_clients->sock, &active_read);
							}
							else if (close_connection < 0) {
								std::cout << "End of file, read_sock: " << it_clients->sock << "\n";
								//close (it_clients->sock);
								FD_CLR(it_clients->sock, &read_set);
								//FD_CLR(it_clients->sock, &active_write);
								it_clients->ready_to_send = 1;
								FD_SET(it_clients->sock, &active_write);
							}
					}
					if (FD_ISSET(it_clients->sock, &write_set) && it_clients->ready_to_send == 1) {
						std::cout << "\x1b[1;96m" << "\n> Found Write socket fd: " << it_clients->sock << "\n\n" << "\x1b[0m";
						writeToClient(it_clients->sock);
						it_clients->send_end = 1; //////////////добавить из HTTP!!!!!!!
						//close (i);
						if (it_clients->send_end == 1) {
							it_clients->ready_to_send = -1;
							FD_CLR(it_clients->sock, &active_write);
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

		int readFromClient(int fd) { //// Сюда приходят данные от браузера GET POST и тд
			long	lenRequest;
			char	buf[BUFSIZE];

			lenRequest = read(fd, buf, BUFSIZE);
			std::string buffer;
			if (lenRequest > 0) {
				std::cout << "\x1b[1;31m" << "\n> HTTP from brauser___fd: " << fd << "\n\n" << "\x1b[0m";
				printf("%s\n", buf);
    			std::cout << "\x1b[1;31m" << "> HTTP from brauser END___fd: " << fd << "\n" << "\x1b[0m";
				buffer.append(buf, lenRequest); //добавила obeedril
				http->initRequest(fd, buffer);
				if (buffer.find("\r\n\r\n") != std::string::npos || buffer.find("\n\n") != std::string::npos) {
					return (-1);
				}
				return (1);
			}
			else 
				return (0);
		}

		int createNewSocket() {
			for (int i = 0; i < maxFd; i++) {
				//std::cout << "Found active socket......." << i << "\n";
				if (FD_ISSET(i, &read_set)) {
					std::cout << "\x1b[1;96m" << "\n> Found Active Listen socket fd: " << i << "\n" << "\x1b[0m";
					std::cout << getFDListenSocket(i) << "\n";
					int num_serv = getFDListenSocket(i);
					if (num_serv != -1) {
						size_client_addr = sizeof(client_addr);
						new_sock = accept(vectorServers[num_serv]->getFdSocket(), (struct sockaddr *)&client_addr, &size_client_addr);
						if (new_sock < 0) {
							error("Error: Accept socket failed");
						}
						t_Client tmp;
						tmp.listen_sock = i;
						tmp.sock = new_sock;
						tmp.client_addr = client_addr;
						tmp.size_client_addr = size_client_addr;
						tmp.ready_to_send = -1;
						tmp.send_end = 0;
						list_clients.push_back(tmp);
						std::cout << "\x1b[1;92m" << "> Create NEW Socket: " << new_sock << "\n" << "\x1b[0m";
						fcntl(new_sock, F_SETFL, O_NONBLOCK);
						FD_SET(new_sock, &active_read);
						if (new_sock >= maxFd) {
							maxFd = new_sock + 1;
						}
					}
				}
			}
			return (0);
		}

		int writeToClient(int fd) {

			size_t readsize = http->getPartAnswer(fd).length();
			send(fd, http->getPartAnswer(fd).c_str(), (int)readsize, 0);
			
			//char buffer[1000] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!"; 
			//send(fd, buffer, strlen(buffer), 0);

			//size_t readsize = http->getPartAnswer(fd).length();
			//send(fd, http->getPartAnswer(fd).c_str(), (int)readsize, 0);
      		std::cout << "\x1b[1;92m" << "\n> Send Message To Client!___fd: " << fd << "\n\n" << "\x1b[0m";
			// send(fd, answer->getAnswer().c_str(), (int)readsize, 0);


			//send(fd, answer->getAnswer().c_str(), (int)readsize, 0);
			//char buffer[1000] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";; // Content-Type - тип запрашиваемого файла
			//size_t readsize = strlen(buffer);
			//send(fd, buffer, (int)readsize, 0); // отправили заголовок
			//char filename[21] = "resources/post.html"; 
				//FILE *file = fopen(filename, "r"); // открываем файл для отправки
				//if (file == NULL) {
				//	exit(-2);
				//}
				//while ((readsize = fread(buffer, sizeof(char), 1000, file)) != 0) {
				//	send(fd, buffer, (int)readsize, 0);
				//} // читаем и отправляем файл по чуть-чуть
			//	fclose(file);
			//send(fd, buffer, strlen(buffer), 0);
			//std::cout << "\x1b[1;92m" << "\n> Send Message To Browser!___fd: " << fd << "\n\n" << "\x1b[0m";

			//char buffer[1000] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!"; 
			//send(fd, buffer, strlen(buffer), 0);
			//size_t readsize = http->getPartAnswer().length();
			//send(fd, http->getPartAnswer().c_str(), (int)readsize, 0);

			return (0);
		}

		int getFDListenSocket(int fd) {
			for (int num_serv = 0; num_serv < count_servers; ++num_serv) {
				if (vectorServers[num_serv]->getFdSocket() == fd) {
					return(num_serv);
				}
			}
			return(-1);
		}

		
};

#endif