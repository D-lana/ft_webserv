#ifndef CGI_HPP
#define CGI_HPP

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h> 
#include <iostream>

// #include <sys/socket.h>
// #include <stdlib.h>
// #include <netinet/in.h>
// #include <iostream>
// #include <sys/types.h>
// #include <netdb.h>
// #include <fcntl.h>
// #include <poll.h>
// #include <vector>
// #include <list>
// #include <algorithm>

// #include "Server.hpp"
// #include "Request.hpp"
// #include "Response.hpp"
// #include "Http.hpp"
// #include "Socket.hpp"

#define PATH_PY "/usr/local/bin/python3"
#define	PATH_SH "/bin/bash"

#define SCRIPT_PY "hello.py"

class CGI {
	private:
		char **env;

	public:

		CGI() {

		}

		~CGI() {

		}

		int createDynamicHtml() {
			pid_t	pid;
			char *cmd[3] = {NULL, NULL, NULL};

			cmd[0] = strdup(PATH_PY);
			cmd[1] = strdup(SCRIPT_PY);
			if (cmd[0] == NULL || cmd[1] == NULL) {
				std::cout << "\x1b[1;70m" << "> Strdup ERROR " << "\n" << "\x1b[0m";
				/// Передать инфо об ошибке
				return (-1);
			}
			pid = fork();
			if (pid == 0) {
				if (execve(PATH_PY, cmd, NULL) == -1) {
					std::cout << "\x1b[1;70m" << "> Execve ERROR " << "\n" << "\x1b[0m";
				}
				exit(3);
			}
			else {
				waitpid(pid, NULL, 0);
			}
			std::cout << "\x1b[1;92m" << "> SUCCES! " << "\n" << "\x1b[0m";
			free (cmd[0]);
			free (cmd[1]);
			return (0);
		}

		// int enviroment() {
		// 	char *key;
		// 	char *value;
		// 	key = strdup("PATH_INFO=");
		// 	key = strdup("PATH_TRANSLATED=");
		// 	key = strdup("QUERY_STRING=");
		// 	return (0);
		// }
		
};

#endif
