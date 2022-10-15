#ifndef CORE_HPP
# define CORE_HPP

#include "Library.hpp"

typedef struct s_Client 
{
	struct sockaddr_in		client_addr;
	socklen_t				size_client_addr;
	int						listen_sock;
	int						sock;
	int						ready_to_send;
	int 					send_end;

}							t_Client;

class Core {
	private:
		Http					*http;
		ServerPairs             *null_ptr1;

		fd_set					active_read, read_set;
		fd_set					active_write, write_set;
		int						maxFd;
		
		int						new_sock;
		struct sockaddr_in		client_addr;
		socklen_t				size_client_addr;

		std::vector<Server *>	vectorServers;
		int						count_servers;
		
		int						close_connection;

		std::list<t_Client>				list_clients;
		std::list<t_Client>::iterator	it_clients;

	public:
		Core(std::vector<Server *> vectorServers_);
		~Core();

		void	run();
		int		createNewSocket();
		int		error(const char* err_type);
		int		writeToClient(int fd);
		int		readFromClient(int fd);	
		int		getFDListenSocket(int fd);
		const	std::string& getRootFromConfig(int fd) const;
		const	ServerPairs& getServerPairs(int fd);
};

#endif
