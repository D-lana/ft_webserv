/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:55:20 by marvin            #+#    #+#             */
/*   Updated: 2022/08/30 17:55:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#define EXTENSION ".conf"



#include <iostream> //del!
#include <cstdlib> //del!
#include <unistd.h> //del!



FtParser::FtParser(const char *argv) : _config(argv) {

    _serverTools = {"listen", "server_name", "autoindex", "index", "root", "upload_path", 
		"client_max_body_size", "error_page", "methods"};
	_locationTools = {"location", "root", "autoindex", "index", "upload_path",
		"redirection", "error_page", "bin_path_py", "path_cgi",  "methods" };
	_configTokens = {"server",  "listen",  "server_name",  "autoindex", 
		"index", "root", "upload_path", "client_max_body_size", "error_page", 
		"methods", "location", "redirection", "path_cgi", "bin_path_py", 
		";", "{", "}" };
}

FtParser::~FtParser() {
}

void FtParser::findEndBrace(std::vector<std::string> &config, 
		std::vector<std::string>::iterator& it) {
	// size_t openBrace = 0;
	// size_t closeBrace = 0;
	if (*(++it) != "{")
		throw std::runtime_error("Invalid syntax in config");
	size_t openBrace = 1;
	size_t closeBrace = 0;
	while (++it < config.end()) {
		if (*it == "}" && (openBrace - closeBrace == 1)) {
		// std::cout << "{ - ок!" <<  std::endl;
			return ;
		}
		else if (*it == "}") {
			++closeBrace;
			// std::cout << "find }. openBrace = " << openBrace << " closeBr = " << closeBrace << std::endl;
		}

		else if (*it == "{") {
			++openBrace;
			// std::cout << "find {. openBrace = " << openBrace << " closeBr = " << closeBrace << std::endl;
		}
		// ++it;
	}
		// std::cout << "*it = " << *it << std::endl;
		}

void FtParser::parse(std::string argv) {
	if (strlen(EXTENSION) > argv.size() || argv.substr((argv.size() - strlen(EXTENSION)), 
			strlen(EXTENSION)) != EXTENSION)
		throw std::runtime_error("Wrong config file");

	std::vector<std::string> config = splitLines(_config);

	std::vector<std::string>::iterator it;
	std::vector<std::string>::iterator start;
	bool check = 0;
	it = config.begin();
	while (it < config.end()) {
		if (*it == "server") {
			start = it;
			// std::cout << "it before" << *it <<  std::endl;
			findEndBrace(config, it);
			// std::cout << "it after" << *it <<  std::endl;
			_serverPairs.push_back(ServerPairs());
			// std::cout << "_serverPairs.size() = " << _serverPairs.size() <<  std::endl;
			serverPairsInit(_serverPairs.size() - 1, config, start, it);
			check = 1;

			// break;
		}
		++it;
		if (check == 0 && it == config.end()) {
			throw std::runtime_error("Cannot find server in config");
		}
	}
	config.clear();
	// for (size_t i = 0; i < _serverPairs.size(); ++i) {
    //     std::cout << "_serverPairs = " << (_serverPairs.back()).getHost() <<  std::endl;
	// 	// std::cout << "_serverPairs.servName = " << _serverPairs.servN <<  std::endl;
	// }

	for (std::vector<ServerPairs>::iterator it = _serverPairs.begin() ; it!=_serverPairs.end() ; ++it) {
        std::cout<<(*it).getServName() <<  std::endl;
		// std::cout<<(*it).getServName() <<  std::endl;
		std::vector<Location> a = (*it).getLocations();
		for (std::vector<Location>::iterator at = a.begin() ; at!=a.end() ; ++at) {
		std::cout<< "Location cgi" << (*at).getLocationPathCgi() <<  std::endl;
		}

	}
	// здесь дальше про порты?
}


std::vector<std::string> FtParser::splitLineOfConfig(std::string token, std::string str) {
	std::vector<std::string> vector;
	size_t i = 0;
	size_t start = str.find(token) + token.size();
	i = start;
	while (i < str.size()) {
		while (isspace(str[i])) {
			++i;
	}
		start = i;
			while (str[i] && !isspace(str[i]))
				++i;
			// std::cout << "str.substr(start, i - start) = " << str.substr(start, i - start) << std::endl;	
			vector.push_back(str.substr(start, i - start));
	}
	return vector;
}


void FtParser::serverPairsInit(size_t index, std::vector<std::string> config, 
	std::vector<std::string>::iterator& start, std::vector<std::string>::iterator& end) {
	
	ConfigData rootTools;
	// ConfigData locationTools;

	while (++start < end) {
			if (*start != "{" && *start != "}") { //????
				for (std::vector<std::string>::iterator it = _serverTools.begin(); it < _serverTools.end(); ++it) {
					std::cout << "*it = " << *it << " >>  *start =" << *start << std::endl;
					if (!(*start).find(*it)) {
						std::cout << "find token, it = " << (*it) << std::endl;
						usleep(100);
						// rootTools.serverData.push_back(*start); //???
						chooseTokenInConfig(*start, *it);
						// break;
					}
					else if (!(*start).find("location")) {
						std::cout << "find location" << std::endl;
						// rootTools.locationData.push_back(*start);
						locationInit(*start, "location", config, start);
						break ;
					}
				}
			}
			// else if (*start == "location") {
			// 	std::cout << "find location" << std::endl;
			// 	// rootTools.locationData.push_back(*start);
			// 	locationInit(*start, "location", config, start);
			// }
		}
}


void FtParser::locationInit(std::string& str, std::string token, std::vector<std::string>& config, 
		std::vector<std::string>::iterator& start) {
	std::vector<std::string> vector;
	std::vector<std::string>::iterator beginLocation = start;
	ConfigData locationTools;
	// size_t pos = 0;
	// size_t i = 0;
	
std::cout << " 175 *start =" << *start << ", str = " << str << ", token = " << token  << std::endl;

	((_serverPairs.back()).getLocations()).push_back(Location());
	// size_t i = str.find(token) + token.size();
	size_t i = 0;
	// size_t i = j;
	std::cout << " 181 *start =" << *start << std::endl;
	while (start < config.end()) {
		std::cout << " 183 *start =" << *start << std::endl;
		while ((*start)[i]) {
			std::cout << " 185 *start =" << *start << std::endl;
			if ((*start)[i] == '}') {
				// finishLocation = start;
				break ;
			}
			++i;
		}
			++start;
			i = 0;
	}
	while (beginLocation < start) {
		// for (size_t i = 0; i < rootTools.locationData.size(); ++i) {

		for (std::vector<std::string>::iterator it = _locationTools.begin(); it < _locationTools.end(); ++it) {
					// std::cout << "*it = " << *it << " >>  *start =" << *start << std::endl;
		if (!(*beginLocation).find(*it)) {
				// std::cout << "find token" << std::endl;
				// rootTools.locationData.push_back(*beginLocation); //???
				chooseTokenInLocation(*beginLocation, *it);
			}
		++beginLocation;
	}
}
		}

void FtParser::chooseTokenInLocation(std::string str, std::string token) {
	// std::cout << "chooseTokenInConfig: token = " << token << std::endl;
		if (token == "location")
			findLocationName(str, token);
		else if (token == "autoindex")
			findLocationAutoIndex(str, token);
		else if (token == "index")
			findLocationIndex(str, token);
		else if (token == "root")
			findLocationRoot(str, token);
		else if (token == "upload_path")
			findLocationUpload(str, token);
		else if (token == "redirection")
			findLocationRedirection(str, token);
		else if (token == "error_page")
			findLocationError(str, token);
		else if (token == "bin_path_py")
			findLocationBinPath(str, token);
		// else if (token == "path_cgi")
		// 	findLocationPathCgi(str, token);
		else if (token == "methods")
			findLocationMethod(str, token);
}

		void FtParser::findLocationName(std::string str, std::string token) {
		std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of location name");
		(((_serverPairs.back()).getLocations()).back()).setLocationName(vector[0]);
		if (vector[0] == "/cgi-bin/")
			(((_serverPairs.back()).getLocations()).back()).setLocationPathCgi(1);
		}

		void FtParser::findLocationAutoIndex(std::string str, std::string token) {
		std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
		if (vector.size() != 1 || (vector[0] != "on" && vector[0] != "off"))
			throw std::runtime_error("Invalid syntax of autoindex (location)");
		if (vector[0] == "on")
		(((_serverPairs.back()).getLocations()).back()).setLocationAutoIndex(1);
		}

		void FtParser::findLocationIndex(std::string str, std::string token) {
		std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of index (location)");
		(((_serverPairs.back()).getLocations()).back()).setLocationIndex(vector[0]);
		}

		void FtParser::findLocationRoot(std::string str, std::string token) {
		std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of root (location)");
		(((_serverPairs.back()).getLocations()).back()).setLocationRoot(vector[0]);
		}

		void FtParser::findLocationUpload(std::string str, std::string token) {
		std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of upload (location)");
		(((_serverPairs.back()).getLocations()).back()).setLocationUploadPath(vector[0]);
		}

		void FtParser::findLocationRedirection(std::string str, std::string token) {
		std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
		if (vector.size() != 2 || (((_serverPairs.back()).getLocations()).back()).getLocationPathCgi() == 1)
			throw std::runtime_error("Invalid syntax of redirection (location)");
		(((_serverPairs.back()).getLocations()).back()).setLocationRedirection(1);
		(((_serverPairs.back()).getLocations()).back()).setLocationIndex(vector[1]);
		if (static_cast<int>(strtod(vector[1].c_str(), 0)) != 302)
			throw std::runtime_error("Wrong redirection code (302 only)"); //???????????????
		}

		void FtParser::findLocationError(std::string str, std::string token) {
			std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
			if (vector.size() < 2)
				throw std::runtime_error("Invalid syntax of error page (location)");
			int code = static_cast<int>(strtod(vector[0].c_str(), 0));
			std::string description = vector[1];
			if (code == 0 || description.empty())
				throw std::runtime_error("Invalid syntax of error page (location)");
		(((_serverPairs.back()).getLocations()).back()).setLocationError(code, description);
		}

		void FtParser::findLocationBinPath(std::string str, std::string token) {
		std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
		if (vector.size() != 1 ||(((_serverPairs.back()).getLocations()).back()).getLocationPathCgi() == 0)
			throw std::runtime_error("Invalid syntax of binpath (location)");
	(((_serverPairs.back()).getLocations()).back()).setLocationBinPath(vector[0]);
		}

		// void findLocationPathCgi(std::string str, std::string token) {

		// }

		void FtParser::findLocationMethod(std::string str, std::string token) {
			std::vector<std::string> vector = FtParser::splitLineOfConfig(token, str);
			if (vector.size() < 1 || vector.size() > 3)
				throw std::runtime_error("Unproper count of methods (location)");
			for (size_t i = 0; i < vector.size(); ++i) {
				if (vector[i] == "GET")
					(((_serverPairs.back()).getLocations()).back()).setLocationMethod("GET");
				else if (vector[i] == "POST")
				(((_serverPairs.back()).getLocations()).back()).setLocationMethod("POST");
				else if (vector[i] == "DELETE")
					(((_serverPairs.back()).getLocations()).back()).setLocationMethod("DELETE");
				else
					throw std::runtime_error("Invalid syntax of method (location)");	
	}
	}

void FtParser::chooseTokenInConfig(std::string str, std::string token) {
	// std::cout << "chooseTokenInConfig: token = " << token << std::endl;
		if (token == "listen")
			findListen(str, token);
		else if (token == "server_name")
			findServerName(str, token);
		else if (token == "autoindex")
			findAutoIndex(str, token);
		else if (token == "index")
			findIndex(str, token);
		else if (token == "root")
			findRoot(str, token);
		else if (token == "upload_path")
			findUpload(str, token);
		else if (token == "client_max_body_size")
			findBodySize(str, token);
		else if (token == "error_page")
			findError(str, token);
		else if (token == "methods")
			findMethod(str, token);
}

	std::vector<std::string> FtParser::splitListen(std::string str) {
	std::vector<std::string> vector;
	size_t i = 0;
	// size_t part = 0;
	size_t dot = 0;

	while(str[i]) {
		// std::cout << "0str + i = " << str[i] << std::endl;	
		if (isdigit(str[i])) {
			++i;
		// std::cout << "1str + i = " << str[i] << std::endl;	
		}
		else if (str[i] == '.') {
			++dot;
			// std::cout << "2str + i = " << str[i] << std::endl;	
			// if (part > 3 || dot > 3)
			if (dot > 3)
				throw std::runtime_error("Invalid syntax in \"listen\": wrong host");
			// part = 0;
			++i;
		}
		else if (str[i] == ':' && i) {
			// std::cout << "str.substr(0, i) = " << str.substr(0, i) << std::endl;	
			// std::cout << "str.substr(i + 1, str.size() = " << str.substr(i + 1, str.size()) << std::endl;	
			vector.push_back(str.substr(0, i));
			vector.push_back(str.substr(i + 1, str.size()));
			return vector;
		}
		else
			throw std::runtime_error("Invalid syntax in \"listen\": no host");
		// ++part;
	}
	// if (!vector.size())
		vector.push_back(str.substr(0, i));
	// else
	// 	throw std::invalid_argument("Parser error: wrong host/port");
	return vector;
}


	void FtParser::findListen(std::string str, std::string token) {

		std::vector<std::string> vector = splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of host or port");
		vector = splitListen(vector[0]);
		if (vector.size() > 1) {
			(_serverPairs.back()).setHost(vector[0]);
			// std::cout << "_serverPairs.end()).getHost= "  << (_serverPairs.back()).getHost() << std::endl;
			(_serverPairs.back()).setPort(static_cast<int>(strtod(vector[1].c_str(), 0))); // нужна ли проверка порта на валидность?
			// std::cout << "_serverPairs.end()).getPort= "  << (_serverPairs.back()).getPort() << std::endl;
		}
		else {
			if (vector[0].find(".") != std::string::npos)
				(_serverPairs.back()).setPort(PORT);
			else
				(_serverPairs.back()).setPort(static_cast<int>(strtod(vector[0].c_str(), 0)));
		}
}

		void FtParser::findServerName(std::string str, std::string token) {
		std::vector<std::string> vector = splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of server name");
		(_serverPairs.back()).setServName(vector[0]);
		}

		void FtParser::findAutoIndex(std::string str, std::string token) {
		std::vector<std::string> vector = splitLineOfConfig(token, str);
		if (vector.size() != 1 || (vector[0] != "on" && vector[0] != "off"))
			throw std::runtime_error("Invalid syntax of autoindex");
		if (vector[0] == "on")
		(_serverPairs.back()).setAutoIndex(1);
		}

		void FtParser::findIndex(std::string str, std::string token) {
		std::vector<std::string> vector = splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of index");
		(_serverPairs.back()).setIndex(vector[0]);
		}

		void FtParser::findRoot(std::string str, std::string token) {
		std::vector<std::string> vector = splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of root");
		(_serverPairs.back()).setRoot(vector[0]);
		}

		void FtParser::findUpload(std::string str, std::string token) {
		std::vector<std::string> vector = splitLineOfConfig(token, str);
		if (vector.size() != 1)
			throw std::runtime_error("Invalid syntax of upload");
		(_serverPairs.back()).setUpload(vector[0]);
		}

	void FtParser::findBodySize(std::string str, std::string token) {
	std::vector<std::string> vector = splitLineOfConfig(token, str);
	if (vector.size() != 1)
		throw std::runtime_error("Invalid syntax of max body size");
	if (vector[0][vector[0].size() - 1] == 'M') {
		vector[0] = vector[0].substr(0, vector[0].size() - 1);
		(_serverPairs.back()).setMaxBodySize(static_cast<int>(strtod(vector[0].c_str(),
				 0)) * 1024 * 1024);
	} else if (isdigit(vector[0][vector[0].size() - 1])) { // только последний?
		(_serverPairs.back()).setMaxBodySize(static_cast<int>(strtod(vector[0].c_str(),
				 0)) * 1024);
	} else {
		throw std::invalid_argument("Invalid syntax of max body size");
		}
	}

	void FtParser::findError(std::string str, std::string token) {
	std::vector<std::string> vector = splitLineOfConfig(token, str);
	if (vector.size() < 2)
		throw std::runtime_error("Invalid syntax of error page");
	int code = static_cast<int>(strtod(vector[0].c_str(), 0));
	std::string description = vector[1];
	if (code == 0 || description.empty())
		throw std::runtime_error("Invalid syntax of error page");
	(_serverPairs.back()).setError(code, description);
	}

	void FtParser::findMethod(std::string str, std::string token) {
	std::vector<std::string> vector = splitLineOfConfig(token, str);
	if (vector.size() < 1 || vector.size() > 3)
		throw std::runtime_error("Unproper count of methods");
	for (size_t i = 0; i < vector.size(); ++i) {
		if (vector[i] == "GET")
			(_serverPairs.back()).setMethod("GET");
		else if (vector[i] == "POST")
			(_serverPairs.back()).setMethod("POST");
		else if (vector[i] == "DELETE")
			(_serverPairs.back()).setMethod("DELETE");
		else
			throw std::runtime_error("Invalid syntax of method");
	
	}
	}

int FtParser::onlySpaces(std::string buf) {
	size_t i = 0;

	while (buf[i]) {
		if (!isspace(buf[i++]))
			return 1;
	}
	return 0;
}

int FtParser::emptyOrComments(std::string buf) {
	if (buf[0] == '#' || buf.empty()) {
		// std::cout << "buf[0] == '#' или buf.empty()) " << std::endl;
		return 1;
	}
	// if (buf.find('#') != std::string::npos) {
		if (buf.find('#')) {
		buf = buf.substr(0, buf.find('#'));
		// std::cout << "new buf = "  << buf << std::endl;
		if (!onlySpaces(buf)) {
			// std::cout << "onlySpaces(buf) = 1" << std::endl;
			return 1;
		}
	}
	return 0;
}

void FtParser::deleteSpaces(std::string *str) {
	
	size_t i = 0;
	while (isspace((*str)[i])) {
			++i;
	}
	*str = (*str).substr(i, (*str).size());
	i = (*str).size() - 1;
	
	while (isspace((*str)[i]) || (*str)[i] == ';') {
			--i;
	}

	if (i <= (*str).size()) // строго меньше??
		*str = (*str).substr(0, i + 1);
		// std::cout << "*str = "  << *str << std::endl;
}

std::vector<std::string> FtParser::checkBraces(std::string buf) {
	std::vector<std::string> vector;
	std::string lineBeforeBraces;
	std::string lineAfterBraces;
	std::string braces;
	std::string tmp;
	size_t i = 0;

	while (buf[i]) {
		if (buf[i] == '}' || buf[i] == '{') {
			lineBeforeBraces = buf.substr(0, i);
			// std::cout << "lineBeforeBraces = " << lineBeforeBraces << std::endl; // !!!!
			deleteSpaces(&lineBeforeBraces);
			// std::cout << "lineBeforeBraces = " << lineBeforeBraces << std::endl; // !!!!
			if (!lineBeforeBraces.empty())
				vector.push_back(lineBeforeBraces);
			lineBeforeBraces.clear();

			tmp = buf.substr(i, buf.size());
			// std::cout << "tmp = " << tmp << std::endl; // !!!!
			braces = tmp.substr(0, 1);
			// std::cout << "braces = " << braces << std::endl; // !!!!
			vector.push_back(braces);
			braces.clear();

			lineAfterBraces = tmp.substr(1, tmp.size());
			// std::cout << "lineAfterBraces = " << lineAfterBraces << std::endl; // !!!!
			// std::cout << "tmp = " << tmp << std::endl; // !!!!
			deleteSpaces(&lineAfterBraces);
			// std::cout << "lineAfterBraces = " << lineAfterBraces << std::endl; // !!!!
			if (!lineAfterBraces.empty())
				vector.push_back(lineAfterBraces);
			lineAfterBraces.clear();
			tmp.clear();
		}
		++i;
	}
	return vector;
}


void FtParser::checkTokens(std::vector<std::string> res) {
	std::vector<std::string>::iterator it;
	std::string str;

	it = res.begin();
	while (it < res.end()) {
		size_t i = 0;
		while (!isspace((*it)[i]))
			++i;
		str = (*it).substr(0, i);
	if (!str.empty() && std::find(_configTokens.begin(), _configTokens.end(), str) == _configTokens.end())
			throw std::runtime_error("Unproper token in config");
		++it;
	}
}


void FtParser::bracesCounter(std::vector<std::string> res) {
	    size_t openBrace = 0;
		size_t closeBrace = 0;
		for (size_t i = 0; i < res.size(); ++i) {
        // std::cout << "vector.at = " << res.at(i) <<  std::endl;
		if (res.at(i) == "{")
			++openBrace;
		else if (res.at(i) == "}")
			++closeBrace;
    }
		if (openBrace != closeBrace)
			throw std::runtime_error("Unproper count of braces in config");
}

std::vector<std::string> FtParser::splitLines(std::string argv) {
// std::vector<std::string> FtParser:splitLines(std::string argv) { // возвращается не ссылка!
	
	std::ifstream file(argv);
	if (!(file.is_open()))
		throw std::runtime_error("Cannot open config file");

	std::string buf;
	std::vector<std::string> split;
	std::vector<std::string> res;

	while (!file.eof()) {
		// std::cout << " -- 5" << std::endl;
		getline(file, buf);
		// std::cout << "buf = " << buf << std::endl; // !!!!
		if (emptyOrComments(buf))
			continue;
		split = checkBraces(buf);

// std::cout << "split = " << split << ", buf = " << buf << std::endl; // !!!!

		if (!split.empty()) {
			for (size_t i = 0; i < split.size(); ++i) {
				res.push_back(split[i]);
				split[i].clear();		
			}
		}
		else {
			deleteSpaces(&buf);
			res.push_back(buf);
		}
		buf.clear();
	}
	res.push_back("");
	file.close();
	bracesCounter(res);
	checkTokens(res);
	return res;
}