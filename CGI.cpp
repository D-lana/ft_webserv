# include "Library.hpp"

CGI::CGI() {

}

CGI::~CGI() {

}

int CGI::createDynamicHtml(char **env, std::string url) {
	pid_t	pid;
	std::cout << "\x1b[1;70m" << "> reateDynamicHtml 1 " << "\n" << "\x1b[0m";
	char **cmd;
	cmd = new char*[COUNT_CMD];
	std::cout << "\x1b[1;70m" << "> reateDynamicHtml 33 " << "\n" << "\x1b[0m";
	for(int i = 0; i < COUNT_CMD; i++) {
		cmd[i] = NULL;
	}
	std::cout << "\x1b[1;70m" << "> reateDynamicHtml 5 " << "\n" << "\x1b[0m";
	// char **env;
	// env = new char*[COUNT_ENV]; /////////////////
	// for(int i = 0; i < COUNT_ENV; i++) {
	// 	env[i] = NULL;
	// }
	std::cout << "\x1b[1;70m" << "> reateDynamicHtml 6 " << "\n" << "\x1b[0m";
	cmd[0] = strdup(PATH_PY);
	cmd[1] = strdup(url.c_str());
	std::cout << "\x1b[1;70m" << "> reateDynamicHtml 2 " << "\n" << "\x1b[0m";
	environment(url, env);
	std::cout << "\x1b[1;70m" << "> reateDynamicHtml 3 " << "\n" << "\x1b[0m";
	if (cmd[0] == NULL || cmd[1] == NULL) {
		std::cout << "\x1b[1;70m" << "> Strdup ERROR " << "\n" << "\x1b[0m";
		/// Передать инфо об ошибке
		return (-1);
	}
	pid = fork();
	if (pid == 0) {
		if (execve(PATH_PY, cmd, env) == -1) {
			std::cout << "\x1b[1;70m" << "> Execve ERROR " << "\n" << "\x1b[0m";
		}
		exit(3);
	}
	else {
		waitpid(pid, NULL, 0);
	}
	std::cout << "\x1b[1;92m" << "> SUCCES! " << "\n" << "\x1b[0m";
	for(int i = 0; i < COUNT_CMD; i++) {
		free(cmd[i]);
	}
	for(int i = 0; i < COUNT_ENV; i++) {
		free(env[i]);
	}
	delete cmd;
	delete env;
	return (0);
}

int CGI::environment(std::string url, char **env) {
	std::string path_info = "PATH_INFO=" + url;
	std::string request_method = "REQUEST_METHOD=";
	request_method.append(REQUEST_METHOD);
	std::string query_string = "QUERY_STRING=";
	query_string.append(QUERY_STRING);

	std::string content_type = "CONTENT_TYPE=";
	content_type.append(CONTENT_TYPE);
	std::string content_length = "CONTENT_LENGTH=";
	content_length.append(CONTENT_LENGTH);
	std::string http_cookie = "HTTP_COOKIE=";
	http_cookie.append(HTTP_COOKIE);


	env[0] = strdup(path_info.c_str());
	env[1] = strdup(request_method.c_str());
	env[2] = strdup(query_string.c_str());
	env[3] = strdup(content_type.c_str());
	env[4] = strdup(content_length.c_str());
	env[5] = strdup(http_cookie.c_str());

	return (0);
}

