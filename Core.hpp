#ifndef CORE_HPP
# define CORE_HPP

# include "Library.hpp"

typedef struct s_Client 
{
	int						listen_sock;
	int						sock;
	struct sockaddr_in		client_addr;
	socklen_t				size_client_addr;
	int						ready_to_send;
	int 					send_end;

}							t_Client;

class Core {
	private:
		Http					*http;
		ServerPairs              *null_ptr1;
		// добавить переменную на keep_alive/keep_stop - обрубить соединение клиента или нет

		fd_set					active_read, read_set;
		fd_set					active_write, write_set;
		int						maxFd;

		//std::map<int, t_Client>		listClients;
		std::list<t_Client>				list_clients;
		std::list<t_Client>::iterator	it_clients;
		
		int						new_sock;
		struct sockaddr_in		client_addr;
		socklen_t				size_client_addr;

		std::vector<Server *>	vectorServers;
		int						count_servers;
		
		int						close_connection;

		std::string				root;


	public:

		Core(std::vector<Server *> vectorServers_);
		void run();
		~Core() {};
		int error (const char* err_type);
		int readFromClient(int fd);
		int createNewSocket();
		int writeToClient(int fd);
		int getFDListenSocket(int fd);
		//const std::string& getRootFromConfig(int fd) const;
		const ServerPairs& getServerPairs(int fd);
};

#endif