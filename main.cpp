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
	if (argc != 2) {
        std::cerr << "No configuration file" << std::endl;
        return 0;
    }
	FILE* fp = fopen(argv[1], "r+");
	if (!fp) {
		std::cerr << "Unproper type of file" << std::endl;
		return 0;
	}
	std::fclose(fp);
	
	FtParser *parser = new FtParser(argv[1]);
	
	try {
		parser->parse(argv[1]);
	}
	catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
	
	
	// /* небольшие правки в то, что было в ветке, с учетом парсера 

	// int count_server = 2;
	int count_server = parser->getServers().size();
	// std::cout << "CHECK: count_server = " << count_server << std::endl;
	// int ports[3] = {8080, 8090};  // храню порты в векторе

	// config

	signal(SIGINT, signalHandler); 
	std::vector<Server*> vectorServers;

/* pveeta: тут вроде недостаточно порта. Нужен доступ ко всем данным объекта ServerPairs, а не только к порту. предлагаю альтернативу ниже

	for (int i = 0; i < count_server; i++) {
		// Server *one_serv = new Server(ports[i]);
		Server *rr_serv = new Server(parser->getPorts()[i]); 
		vectorServers.push_back(rr_serv);
	}
	*/


	//pveeta: альтернатива:
	for (std::vector<ServerPairs>::iterator it = parser->getServers().begin();  
				it!= parser->getServers().end(); ++it)	 {
		Server *ff_serv = new Server(*it);
		// std::cout << "CHECK: (*it).getPort() = " << (*it).getPort() << std::endl;
		// std::cout << "проверка адреса ячейки  one_serv >>> " << ff_serv << "\n"; // проверка адреса ячейки
		// vectorServers.push_back(one_serv);
		vectorServers.push_back(ff_serv);
		//std::cout << "проверка адреса ячейки vectorServers.back() >>> " << vectorServers.back() << "\n"; // проверка адреса ячейки
	}
	Core* main_core = new Core(vectorServers);
	while (1) {
		main_core->run();
		if (gFlagExit == 1)
			break;
	}
	std::cout << "идем в чистку!>>> " << &main_core  << "\n"; // проверка адреса ячейки

	// */
	// добавила чистку:
	delete parser;
	delete main_core;
	for (int i = 0; i < count_server; i++) {
		delete vectorServers[i];
	}
}
