#include "Server.hpp"

#define ADDRESS INADDR_ANY //pveeta: предлагаю удалить

//pveeta: предлагаю убрать этот конструктор и заменить на следующий
/*Server::Server(int port) {
	opt = 1;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		error("Error: Creating socket failed");
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	// setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, (char*)&opt, sizeof(opt)); // добавила, чтобы не вылетало видео 
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(ADDRESS);
	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		error("Error: Binding socket failed");
	}
	if (listen(sock, 32) < 0) {
		error("Error: Listening socket failed");
	}
}
*/

Server::Server(const ServerPairs& serv) : _serv(serv) { //pveeta: альтернативный конструктор
	opt = 1;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		error("Error: Creating socket failed");
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	// setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, (char*)&opt, sizeof(opt)); // добавила, чтобы не вылетало видео 
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(serv.getPort());
	addr.sin_addr.s_addr = serv.getHost();
	std::cout << "CHECK: serv.getPort() = " << serv.getPort() << ", addr.sin_port = " << addr.sin_port 
	<< ", serv.getHost() = "<< serv.getHost() << ", addr.sin_addr.s_addr = " << addr.sin_addr.s_addr << std::endl;
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
