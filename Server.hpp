#ifndef SERVER_HPP
# define SERVER_HPP

# include "Library.hpp"

class Server {
	
	private:

		int opt;
		int sock;
		struct sockaddr_in addr;
		const ServerPairs& serv_pairs;



	public:

		Server(const ServerPairs& serv); 
		~Server();

		int		error(const char* err_type);
		int		getFdSocket();
		const	std::string& getRootFromConfig() const;
		const	ServerPairs& getServerPairs() const;
};

#endif