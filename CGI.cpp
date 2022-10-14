# include "Library.hpp"

CGI::CGI() {

}

CGI::~CGI() {

}

int CGI::createDynamicHtml(char **env, std::string url) {
	pid_t	pid;
	char **cmd;
	cmd = new char*[COUNT_CMD];
	for(int i = 0; i < COUNT_CMD; i++) {
		cmd[i] = NULL;
	}
	cmd[0] = selectionTypeScript(url);
	cmd[1] = strdup(url.c_str());
	std::cout << "\x1b[1;92m" << "> select script success " << "\n" << "\x1b[0m";
	if (cmd[0] == NULL || cmd[1] == NULL) {
		std::cout << "\x1b[1;70m" << "> Strdup ERROR " << "\n" << "\x1b[0m";
		/// Передать инфо об ошибке
		return (-1);
	}
	pid = fork();
	if (pid != 0) {
		waitpid(pid, NULL, 0);
	}
	else if (pid == 0) {
		std::cout << "\x1b[1;92m" << "> cmd[0] |" << cmd[0] << "|\n" << "\x1b[0m";
		std::cout << "\x1b[1;92m" << "> cmd[1] |" << cmd[1] << "|\n" << "\x1b[0m";
		std::cout << "\x1b[1;92m" << "> PATH_PY |" << PATH_PY << "|\n" << "\x1b[0m";
		if (execve(cmd[0], cmd, env) == -1) {
			std::cout << "\x1b[1;70m" << "> Execve ERROR " << "\n" << "\x1b[0m";
		}
		exit(0);
	}
	std::cout << "\x1b[1;92m" << "> SUCCESS! " << "\n" << "\x1b[0m";
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

// int CGI::environment(std::string url, char **env) {
// 	std::string path_info = "PATH_INFO=" + url;
// 	std::string request_method = "REQUEST_METHOD=";
// 	request_method.append(REQUEST_METHOD);
// 	std::string query_string = "QUERY_STRING=";
// 	query_string.append(QUERY_STRING);

// 	std::string content_type = "CONTENT_TYPE=";
// 	content_type.append(CONTENT_TYPE);
// 	std::string content_length = "CONTENT_LENGTH=";
// 	content_length.append(CONTENT_LENGTH);
// 	std::string http_cookie = "HTTP_COOKIE=";
// 	http_cookie.append(HTTP_COOKIE);


// 	env[0] = strdup(path_info.c_str());
// 	env[1] = strdup(request_method.c_str());
// 	env[2] = strdup(query_string.c_str());
// 	env[3] = strdup(content_type.c_str());
// 	env[4] = strdup(content_length.c_str());
// 	env[5] = strdup(http_cookie.c_str());

// 	return (0);
// }

char *CGI::selectionTypeScript(std::string url) {
	std::cout << "------selectionTypeScript--------: " << url << std::endl;
    std::string s; // сюда будем класть считанные строки
	std::string s_2;
	const char *ss = url.c_str();
    std::ifstream file_read(ss); // файл из которого читаем (для линукс путь будет выглядеть по другому)
	std::getline(file_read, s);
	std::cout << "-------s: " << s << std::endl;
	// что нибудь делаем со строкой //#!/usr/local/bin/python3
	size_t pos = s.find("#!");
	if (pos != std::string::npos && pos == 0) {
		std::cout << "Found at pos = " << pos << "\n";
		s_2 = s.substr(2);
	} 	else {
		std::cout << "Not found\n";
	}
    std::cout << "--------NEW s: " << s_2 << std::endl;
    file_read.close();
	file_read.clear();
	char *tmp =strdup(s_2.c_str());
	if (strncmp(PATH_PY, tmp, strlen(PATH_PY) - 1) == 0) {
		free(tmp);
		return(strdup(PATH_PY));
	}
	return(tmp);
}

