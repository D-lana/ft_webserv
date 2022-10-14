#include "Library.hpp"

bool gFlagExit = 0;

void signalHandler( int signum ) {
	(void)signum;
   std::cout << "\x1b[1;95m" << "\b\b>>>>> Bye-bye! <<<<<\n" << "\x1b[0m"; 
	gFlagExit = 1; 
}

int main(int argc, const char* argv[])
{
	
	//проверка валидности
	if (argc > 2) {
        std::cerr << "Enter one configuration file" << std::endl;
        return 0;
    }
	const char* config;
	if (argc == 1) {
		config = DEFAULT_CONFIG;
    }
	else {
		config = argv[1];
	}
	FILE* fp = fopen(config, "r+");
	if (!fp) {
		std::cerr << "Unproper type of file" << std::endl;
		return 0;
	}
	std::fclose(fp);
	
	FtParser *parser = new FtParser(config);
	try {
		parser->parse(config);
	}
	catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
		return 0;
    }
	
	int count_server = parser->getServers().size();
	signal(SIGINT, signalHandler); 
	std::vector<Server*> vectorServers;

	for (std::vector<ServerPairs>::iterator it = parser->getServers().begin();  
				it!= parser->getServers().end(); ++it)	 {
		Server *ff_serv = new Server(*it);
		vectorServers.push_back(ff_serv);
	}
	Core* main_core = new Core(vectorServers);
	while (1) {
		main_core->run();
		if (gFlagExit == 1)
			break;
	}
	delete parser;
	delete main_core;
	for (int i = 0; i < count_server; i++) {
		delete vectorServers[i];
	}
	return 0;
}
