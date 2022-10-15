// #include "Core.hpp"
#include "Library.hpp"

Core::Core(std::vector<Server *> vectorServers_) : vectorServers(vectorServers_) {
	http = new Http();
	null_ptr1 = NULL;
	maxFd = 0;
	count_servers = vectorServers.size();
	FD_ZERO(&active_read);
	FD_ZERO(&active_write);

	for (int i = 0; i < count_servers; ++i) {
		FD_SET(vectorServers[i]->getFdSocket(), &active_read);
		std::cout << "\x1b[1;92m" << "> Server <" << vectorServers[i]->getServerPairs().getServName();
		std::cout << "\x1b[1;92m" << "> listen port: " << vectorServers[i]->getServerPairs().getPort();
		std::cout << "\n" << "\x1b[0m";
		if (vectorServers[i]->getFdSocket()  >= maxFd) {
			maxFd = vectorServers[i]->getFdSocket() + 1;
		}
	}
}

Core::~Core() { 
	delete http;
}

void	Core::run() {
	this->read_set = this->active_read;
	this->write_set = this->active_write;
	if (select(maxFd, &this->read_set, &this->write_set, 0, 0) < 0) {
		return ;
	}
	createNewSocket();
	for (it_clients = list_clients.begin(); it_clients != list_clients.end(); ++it_clients) {
		if (FD_ISSET(it_clients->sock, &this->read_set) && it_clients->ready_to_send == -1) {
			close_connection = readFromClient(it_clients->sock);
			if (close_connection == 0) {
				close (it_clients->sock);
				FD_CLR(it_clients->sock, &active_read);
			}
			else if (close_connection < 0) {
				FD_CLR(it_clients->sock, &this->read_set);
				it_clients->ready_to_send = 1;
				FD_SET(it_clients->sock, &active_write);
			}
		}
		if (FD_ISSET(it_clients->sock, &write_set) && it_clients->ready_to_send == 1) {
			it_clients->send_end = writeToClient(it_clients->sock);
			if (it_clients->send_end == 1) {
				it_clients->ready_to_send = -1;
				FD_CLR(it_clients->sock, &active_write);
			}
		}
	}
}

int	Core::readFromClient(int fd) {
	long		lenRequest;
	char		buf[BUFSIZE];
	std::string	buffer;

	lenRequest = read(fd, buf, BUFSIZE);
	if (lenRequest > 0) {
		buffer.append(buf, lenRequest);
		ServerPairs tmp_servPairs; 
		tmp_servPairs = getServerPairs(fd);
		if (http->initRequest(fd, buffer, tmp_servPairs) == true) {
			return (-1);
		}
		return (1);
	}
	else 
		return (0);
}

int	Core::writeToClient(int fd) {	
	std::string part_answer = http->getPartAnswer(fd);
	send(fd, part_answer.c_str(), part_answer.length(), 0);
	if (http->getEndAnswer() == true) {
		http->deleteRequest(fd);
		return(1);
	}
	return (0);
}

int	Core::createNewSocket() {
	for (int i = 0; i < maxFd; i++) {
		if (FD_ISSET(i, &read_set)) {
			int num_serv = getFDListenSocket(i);
			if (num_serv != -1) {
				size_client_addr = sizeof(client_addr);
				new_sock = accept(vectorServers[num_serv]->getFdSocket(), (struct sockaddr *)&client_addr, &size_client_addr);
				if (new_sock < 0) {
					error("Error: Accept socket failed");
				}
				t_Client tmp;
				tmp.listen_sock = i;
				tmp.sock = new_sock;
				tmp.client_addr = client_addr;
				tmp.size_client_addr = size_client_addr;
				tmp.ready_to_send = -1;
				tmp.send_end = 0;
				list_clients.push_back(tmp);
				fcntl(new_sock, F_SETFL, O_NONBLOCK);
				FD_SET(new_sock, &active_read);
				if (new_sock >= maxFd) {
					maxFd = new_sock + 1;
				}
			}
		}
	}
	return (0);
}

int	Core::getFDListenSocket(int fd) {
	for (int num_serv = 0; num_serv < count_servers; ++num_serv) {
		if (vectorServers[num_serv]->getFdSocket() == fd) {
			return(num_serv);
		}
	}
	return(-1);
}

const ServerPairs&	Core::getServerPairs(int fd) {
	int listen_sock = -1;
	for (std::list<t_Client>::iterator it = list_clients.begin(); it != list_clients.end(); ++it) {
		if (it->sock == fd) {
			listen_sock = it->listen_sock;
		}
	}
	for (int num_serv = 0; num_serv < count_servers; ++num_serv) {
		if (vectorServers[num_serv]->getFdSocket() == listen_sock) {
			return (vectorServers[num_serv]->getServerPairs());
		}
	}
	return *null_ptr1;
}

int	Core::error(const char* err_type) {
	std::cerr << err_type << std::endl;
	exit(EXIT_FAILURE);
}
