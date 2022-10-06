#ifndef SERVER_HPP
# define SERVER_HPP

# include "library.hpp"

class Server {
	
	private:

		int opt;
		int sock;
		struct sockaddr_in addr;
		const ServerPairs& serv_pairs;

		int error (const char* err_type);

	public:

		Server(const ServerPairs& serv); 
		~Server();
		int getFdSocket();
		const std::string& getRootFromConfig() const;
		const ServerPairs& getServerPairs() const;
};

#endif