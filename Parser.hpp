#ifndef PARSER_HPP
# define PARSER_HPP

# include "Library.hpp"

class FtParser {
	public:

		FtParser(const char* config);
		virtual ~FtParser();
		void parse(std::string argv);
		std::vector<ServerPairs>& getServers();
		std::vector<u_short>& getPorts();
    
    private:

		FtParser();
        std::vector<std::string> splitLines(std::string argv);
        int onlySpaces(std::string buf);
        int emptyOrComments(std::string buf);
        void deleteSpaces(std::string *str);
        std::vector<std::string> checkBraces(std::string buf);
        void bracesCounter(std::vector<std::string> res);
        void checkTokens(std::vector<std::string> res);
        std::vector<std::string>::iterator findEndBrace(std::vector<std::string> &config, 
				std::vector<std::string>::iterator it);

		void serverPairsInit(size_t index,
				std::vector<std::string>::iterator start, std::vector<std::string>::iterator end);
		
		void chooseTokenInConfig(std::string str, std::string token, size_t index, size_t num);
		std::vector<std::string> splitLineOfConfig(std::string token, std::string str);
		void findListen(std::string str, std::string token, size_t index);
		std::vector<std::string> splitListen(std::string str);
		void findServerName(std::string str, std::string token, size_t index);
		void findAutoIndex(std::string str, std::string token, size_t index);
		void findIndex(std::string str, std::string token, size_t index);
		void findRoot(std::string str, std::string token, size_t index);
		void findUpload(std::string str, std::string token, size_t index);
		void findBodySize(std::string str, std::string token, size_t index);
		void findError(std::string str, std::string token, size_t index);
		void findMethod(std::string str, std::string token, size_t index);

		void chooseTokenInLocation(std::string token, std::string str, Location& location, size_t num);
		
		std::vector<std::string>::iterator locationInit(size_t index, 
	std::vector<std::string>::iterator start, std::vector<std::string>::iterator end);

		void findLocationName(std::string str, std::string token, Location& location);
		void findLocationAutoIndex(std::string str, std::string token, Location& location);
		void findLocationIndex(std::string str, std::string token, Location& location);
		void findLocationRoot(std::string str, std::string token, Location& location);
		void findLocationUpload(std::string str, std::string token, Location& location);
		void findLocationRedirection(std::string str, std::string token, Location& location);
		void findLocationError(std::string str, std::string token, Location& location);
		void findLocationBinPathPy(std::string str, std::string token, Location& location);
		void findLocationBinPathSh(std::string str, std::string token, Location& location);
		void findLocationMethod(std::string str, std::string token, Location& location);
		void checkInfo(void);

		ConfigTokens			_configTokens;
		std::vector<ServerPairs> _serverPairs;
		std::vector<u_short> _allPorts;
		const char* _config;
	};

#endif