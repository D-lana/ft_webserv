#ifndef CGI_HPP
# define CGI_HPP

# include "Library.hpp"

class CGI {
	private:
		//char **env;
		//char **cmd;

	public:

		CGI();
		~CGI();

		int createDynamicHtml(char **env, std::string url);
		int environment(std::string url, char **env);
		char *selectionTypeScript(std::string url);
};

#endif
