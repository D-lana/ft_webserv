/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerPairs.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:46:21 by marvin            #+#    #+#             */
/*   Updated: 2022/09/03 20:46:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerPairs.hpp"

ServerPairs::ServerPairs() {

	};

ServerPairs::~ServerPairs() {

	};

void ServerPairs::setPort(const int &port) {
	_port = htons(port);
};

void ServerPairs::setHost(const std::string &host) {
	_host = inet_addr(host.c_str());
};

const u_short& ServerPairs::getPort() const {
	return _port;
};

const in_addr_t& ServerPairs::getHost() const {
	return _host;
};

void ServerPairs::setServName(const std::string &serverName) {
	_servName = serverName;
};

void ServerPairs::setAutoIndex(const bool &autoIndex) {
	_autoIndex = autoIndex;
};

void ServerPairs::setRoot(const std::string &root) {
	_root = root;
};

void ServerPairs::setIndex(const std::string &index) {
	_index = index;
};

void ServerPairs::setUpload(const std::string &path) {
	_uploadPath = path;
};

void ServerPairs::setMaxBodySize(const int &maxBodySize) {
	_maxBodySize = maxBodySize;
};

void ServerPairs::setError(const int &code, const std::string &description) {
	_errorCode = code;
	_errorDescription = description;
};

void ServerPairs::setMethod(const std::string &method) {
	_method = method;
}