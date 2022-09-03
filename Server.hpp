#ifndef SERVER_HPP
# define SERVER_HPP

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
#define BUFSIZE 1024
#define ADDRESS INADDR_ANY

class Server {
	
	private:
		int i, err, opt = 1;
		int sock;
		int maxFd = 0;
		struct sockaddr_in addr;

		int error (const char* err_type) {
			std::cerr << err_type << std::endl;
			exit(EXIT_FAILURE);
		}

	public:

		Server() {
			sock = socket(PF_INET, SOCK_STREAM, 0);
			if (sock < 0) {
				error("Error: Creating socket failed");
			}
			setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

			// заполняем адресную структуру и связываем сокет с любым адресом
			addr.sin_family = AF_INET;
			addr.sin_port = htons(PORT);
			addr.sin_addr.s_addr = ADDRESS;
			if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
				error("Error: Binding socket failed");
			}

			// Создаем очередь на 32 входящих запроса соединения
			if (listen(sock, 32) < 0) {
				error("Error: Listening socket failed");
			}

			// Подготавливаем множества дескрипторов каналов ввода-вывода
			// Для простоты не вычисляем максимальное значение дескриптора 
			//а далее будем проверять все дескрипторы вплодь до максимального FD_SETSIZE;
			std::cout << "LISTEN SOCK - " << sock << "\n";
			if (sock >= maxFd) {
				maxFd = sock + 1;
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
