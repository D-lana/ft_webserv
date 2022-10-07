#ifndef CGI_HPP
# define CGI_HPP

# include "Library.hpp"

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
