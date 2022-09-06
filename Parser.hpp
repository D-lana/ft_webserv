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
#include <cstdio>
#include <algorithm>
#include <iostream>

#define PORT 8080

struct ConfigData {
		std::vector<std::string>			serverData;
		std::vector<std::string>			locationData;
		std::map<std::string, int>			serverTokens;
		std::map<std::string, std::string>	errorsMap;
		std::vector<std::string>			errorPage;
		std::vector<std::string>			autoindexPage;
	};

class FtParser {
	public:

		FtParser(const char* config);
		virtual ~FtParser();
		void parse(std::string argv);

    
    private:

		FtParser();
        std::vector<std::string> splitLines(std::string argv);
        int onlySpaces(std::string buf);
        int emptyOrComments(std::string buf);
        void deleteSpaces(std::string *str);
        std::vector<std::string> checkBraces(std::string buf);
        void bracesCounter(std::vector<std::string> res);
        void checkTokens(std::vector<std::string> res);
        void findEndBrace(std::vector<std::string> &config, std::vector<std::string>::iterator& it);

		void serverPairsInit(size_t index, std::vector<std::string> file, 
			std::vector<std::string>::iterator& start, std::vector<std::string>::iterator& end);
		
		void chooseTokenInConfig(std::string str, std::string token);
		std::vector<std::string> splitLineOfConfig(std::string token, std::string str);
		void findListen(std::string str, std::string token);
		std::vector<std::string> splitListen(std::string str);
		void findServerName(std::string str, std::string token);
		void findAutoIndex(std::string str, std::string token);
		void findIndex(std::string str, std::string token);
		void findRoot(std::string str, std::string token);
		void findUpload(std::string str, std::string token);
		void findBodySize(std::string str, std::string token);
		void findError(std::string str, std::string token);
		void findMethod(std::string str, std::string token);


        std::vector<std::string>			_serverTools;
		std::vector<std::string>			_locationTools;
        std::vector<std::string>            _configTokens;
		// std::map<std::string, int>			_configTokens;

		std::vector<ServerPairs> _serverPairs;
		const char* _config;

	};

#endif