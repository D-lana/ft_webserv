#include <iostream>
#include <vector>

#include "Core.hpp"

#define ADDRESS INADDR_ANY

int main() {

	// config
	int count_server = 2;
	int ports[3] = {8080, 8090};
	// config

	std::vector<Server*> vectorServers;
	for (int i = 0; i < count_server; i++) {
		Server *one_serv = new Server(ports[i]);
		//std::cout << one_serv << "\n"; // проверка адреса ячейки
		vectorServers.push_back(one_serv);
		//std::cout << vectorServers.back() << "\n"; // проверка адреса ячейки
	}
	Core main_core(vectorServers);
	//std::cout << &main_core  << "\n"; // проверка адреса ячейки
}
