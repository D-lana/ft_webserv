#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "library.hpp"

struct ConfigTokens {
    public:

    	std::vector<std::string>			serverData;
		std::vector<std::string>			locationData;
		std::map<std::string, int>			serverTokens;
		std::map<std::string, std::string>	errorMap;
		std::vector<std::string>			errorPage;
		std::vector<std::string>			autoindexPage;


        ConfigTokens();
        // ConfigTokens(int);
        ~ConfigTokens();


};

#endif