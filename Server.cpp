#include "Library.hpp"

Server::Server(const ServerPairs& serv_in) : serv_pairs(serv_in) {
	opt = 1;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		error("Error: Creating socket failed");
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, (char*)&opt, sizeof(opt)); // добавила, чтобы не вылетало видео 
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(serv_pairs.getPort());
	addr.sin_addr.s_addr = serv_pairs.getHost();
	std::cout << "CHECK: serv.getPort() = " << serv_pairs.getPort() << ", addr.sin_port = " << addr.sin_port 
	<< ", serv.getHost() = "<< serv_pairs.getHost() << ", addr.sin_addr.s_addr = " << addr.sin_addr.s_addr << std::endl;
	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		error("Error: Binding socket failed");
	}
	if (listen(sock, 32) < 0) {
		error("Error: Listening socket failed");
	}
};

Server::~Server() {
	close(sock);
}

int Server::getFdSocket() {
	return (sock);
}

const std::string& Server::getRootFromConfig() const { 
	return(serv_pairs.getRoot());
}

const ServerPairs& Server::getServerPairs() const {
	return(serv_pairs);
}

int Server::error(const char* err_type) {
	std::cerr << err_type << std::endl;
	exit(EXIT_FAILURE);
}