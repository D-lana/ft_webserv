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
	it = config.begin();
	while (it < config.end()) {
		if (*it == "server") {
			start = it;
			// std::cout << "it before" << *it <<  std::endl;
			findEndBrace(config, it);
			std::cout << "it after" << *it <<  std::endl;
			_serverPairs.push_back(ServerPairs());
			// std::cout << "_serverPairs.size() = " << _serverPairs.size() <<  std::endl;
			serverPairsInit(_serverPairs.size() - 1, config, start, it);

			break;
		}
		if (++it == config.end()) {
			throw std::runtime_error("Cannot find server in config");
		}
	}
	config.clear();
	// здесь дальше про порты?
}

// остановилась здесь

void FtParser::serverPairsInit(size_t index, std::vector<std::string> config, 
	std::vector<std::string>::iterator& start, std::vector<std::string>::iterator& end) {
	
	ConfigData rootTools;
	std::cout << "start = " << *start <<  std::endl;	
	std::cout << "start + 2= " << *(start + 2) <<  std::endl;
	std::cout << "end -1 = " << *(end -1) <<  std::endl;
	// std::cout << "rootTools.serverData.size() = " << rootTools.serverData.size() <<  std::endl;
	while (start < end) {
		// for (size_t i = 0; i < rootTools.serverData.size(); ++i) {
			if (*start == "location") {
				std::cout << "find location" << std::endl;
				// locationInit(index, config, start, end);
			}
			else if (std::find(_serverTools.begin(), _serverTools.end(), *start) != _serverTools.end()) {
				rootTools.serverData.push_back(*start);
				std::cout << "find token" << std::endl;
				// fillConfig(rootTools.servParams[i], config[start], index, i);
			}
		// }
		++start;
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