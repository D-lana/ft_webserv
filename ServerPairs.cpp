#include "Library.hpp"

ServerPairs::ServerPairs() {
	_port = 0;
    _host = 0;
    _servName.clear();
    _autoIndex = 0;
    _root.clear();
    _index.clear();
    _uploadPath.clear();
    _maxBodySize = -1;
    _errorCode = 0;
    _errorDescription.clear();
    _method.clear();
	};

ServerPairs::~ServerPairs() {
	};

void ServerPairs::setPort(const int &port) {
	// _port = htons(port);
	_port = port;
};

void ServerPairs::setHost(const std::string &host) {
	_host = inet_addr(host.c_str());
	// _host = host; // ????
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

std::vector<Location>& ServerPairs::getLocations() {
	return _locations;
};

const std::string& ServerPairs::getServName() {
	return _servName;
};

const u_short& ServerPairs::getPort() const {
	return _port;
};

const in_addr_t& ServerPairs::getHost() const {
	return _host;
};

const std::string& ServerPairs::getRoot() const {
	return _root;
};

const std::string& ServerPairs::getIndex() {
	return _index;
};

const std::string& ServerPairs::getUpload() {
	return _uploadPath;
};
const int& ServerPairs::getBodySize() {
	return _maxBodySize;
};

ServerPairs &ServerPairs::operator=(const ServerPairs &other) {
	if (this == &other)
		return(*this);
	this->_autoIndex = other._autoIndex;
	this->_errorCode = other._errorCode;
	this->_errorDescription = other._errorDescription;
	this->_host = other._host;
	this->_index = other._index;
	this->_locations = other._locations;
	this->_maxBodySize = other._maxBodySize;
	this->_method = other._method;
	this->_port = other._port;
	this->_root = other._root;
	this->_servName = other._servName;
	this->_uploadPath = other._uploadPath;
	return(*this);
}