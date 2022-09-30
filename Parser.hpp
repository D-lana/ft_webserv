/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:51:18 by marvin            #+#    #+#             */
/*   Updated: 2022/08/29 22:51:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include "ServerPairs.hpp"
#include "ConfigTokens.hpp"
#include <cstdio>
#include <algorithm>
#include <iostream>

#define PORT 8080

// enum serverTokens {
// 	Host,
// 	Port,
// 	Server_name,
// 	Autoindex,
// 	Index,
// 	Root,
// 	Upload_path,
// 	Client_max_body_size,
// 	Error_page,
// 	Methods,
// 	Redirection // ???
// 	};

// enum locationTokens {
// 	Location_name,
// 	Root,
// 	Autoindex, 
// 	Index, 
// 	Upload_path,
// 	Redirection,
// 	Error_page,
// 	Bin_path_py,
// 	Path_cgi, 
// 	Methods 
// 	};

// enum configTokens {
// 	"server",  
// 	"listen", 
// 	 "server_name",  
// 	 "autoindex",
// 	 "index", 
// 	 "root", 
// 	 "upload_path", 
// 	 "client_max_body_size", 
// 	 "error_page", 
// 	"methods", 
// 	"location", 
// 	"redirection", 
// 	"path_cgi",
// 	"bin_path_py", 
// 	";", 
// 	"{", 
// 	"}" 
// 	};


// struct ConfigTokens {
// 		std::vector<std::string>			serverData;
// 		std::vector<std::string>			locationData;
// 		std::map<std::string, int>			serverTokens;
// 		std::map<std::string, std::string>	errorMap;
// 		std::vector<std::string>			errorPage;
// 		std::vector<std::string>			autoindexPage;

// 	ConfigTokens();
// 	ConfigTokens(int key);
// 	~ConfigTokens();
		
// 	};

class FtParser {
	public:

		FtParser(const char* config);
		virtual ~FtParser();
		void parse(std::string argv);
		std::vector<ServerPairs>& getServers();
		std::vector<u_short>& getPorts();
		// u_short* getPorts();
    
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
		// void findLocationPathCgi(std::string str, std::string token, Location& location);
		void findLocationMethod(std::string str, std::string token, Location& location);

		void checkInfo(void);
		



        // std::vector<std::string>			_serverTools;
		// std::vector<std::string>			_locationTools;
        // std::vector<std::string>            _configTokens;
		// std::map<std::string, int>			_configTokens;
		ConfigTokens			_configTokens;//  ft::ValidConfigKeys _validConfigParams;


// 		FtParser::FtParser(const char *argv) : _config(argv) {

//     _serverTools = {"listen", "server_name", "autoindex", "index", "root", "upload_path", 
// 		"client_max_body_size", "error_page", "methods"};
// 	_locationTools = {"location", "root", "autoindex", "index", "upload_path",
// 		"redirection", "error_page", "bin_path_py", "path_cgi",  "methods" };
// 	_configTokens = {"server",  "listen",  "server_name",  "autoindex", 
// 		"index", "root", "upload_path", "client_max_body_size", "error_page", 
// 		"methods", "location", "redirection", "path_cgi", "bin_path_py", 
// 		";", "{", "}" };
// }

		std::vector<ServerPairs> _serverPairs;
		std::vector<u_short> _allPorts;
		const char* _config;

	};

#endif