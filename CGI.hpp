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
		char **cmd;

	public:

		CGI();
		~CGI();

		int createDynamicHtml(std::string url);
		int enviroment(std::string url);
};

#endif
