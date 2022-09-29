#include <iostream>
#include <vector>
#include <list>
#include <iterator>
//#include "Server.hpp"
#include "Core.hpp"
#include "Parser.hpp"

#define ADDRESS INADDR_ANY

int main(int argc, const char* argv[])
{
	
	// проверка валидности
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

	std::vector<Server*> vectorServers;
	for (int i = 0; i < count_server; i++) {
		// Server *one_serv = new Server(ports[i]);
		Server *one_serv = new Server(parser->getPorts()[i]);
		std::cout << "CHECK: parser->getPorts()[i] = " << parser->getPorts()[i] << std::endl;
		std::cout << "проверка адреса ячейки  one_serv >>> " << one_serv << "\n"; // проверка адреса ячейки
		vectorServers.push_back(one_serv);
		std::cout << "проверка адреса ячейки vectorServers.back() >>> " << vectorServers.back() << "\n"; // проверка адреса ячейки
	}
	Core main_core(vectorServers);

	std::cout << "проверка адреса ячейки main_core >>> " << &main_core  << "\n"; // проверка адреса ячейки

	// */
	// добавила чистку:
	delete parser;
	for (int i = 0; i < count_server; i++) {
		delete vectorServers[i];
	}
}
