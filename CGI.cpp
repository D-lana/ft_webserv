# include "Library.hpp"

CGI::CGI() {

}

CGI::~CGI() {

}

int	CGI::createDynamicHtml(char **env, std::string url) {
	pid_t	pid;
	char	**cmd;

	cmd = new char*[COUNT_CMD];
	for(int i = 0; i < COUNT_CMD; i++) {
		cmd[i] = NULL;
	}
	cmd[0] = selectionTypeScript(url);
	cmd[1] = strdup(url.c_str());
	if (cmd[0] == NULL || cmd[1] == NULL) {
		return (-1);
	}
	pid = fork();
	if (pid != 0) {
		waitpid(pid, NULL, 0);
	}
	else if (pid == 0) {
		if (execve(cmd[0], cmd, env) == -1) {
			std::cout << "\x1b[1;70m" << "> ERROR: Execve fail." << "\n" << "\x1b[0m";
		}
		exit(0);
	}
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

char*	CGI::selectionTypeScript(std::string url) {

    std::string		s; 
	std::string		s_2;
	const char *ss = url.c_str();
    std::ifstream file_read(ss);
	std::getline(file_read, s);
	size_t pos = s.find("#!");
	if (pos != std::string::npos && pos == 0) {
		s_2 = s.substr(2);
	} 
	else {
		std::cout << "\x1b[1;70m" << "> ERROR: CGI script unknown format." << "\n" << "\x1b[0m";
	}
    file_read.close();
	file_read.clear();
	char *tmp =strdup(s_2.c_str());
	if (strncmp(PATH_PY, tmp, strlen(PATH_PY) - 1) == 0) {
		free(tmp);
		return(strdup(PATH_PY));
	}
	return(tmp);
}
