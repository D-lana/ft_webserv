#include "Processor.hpp"

Processor::Processor(std::string _url) {

    path = "resources";
    url = _url;
    newUrl = path.append(url);

    std::cout << "newUrl " << "|" << newUrl << "|" << std::endl;


}


// std::string Processor::checkFile() {
    void Processor::checkFile() {
        char arr[newUrl.length() + 1];
        strcpy(arr, newUrl.c_str());
        Response *response = new Response();
        pFile = fopen(arr, "r");

        if (pFile!=NULL)
        {
            response->setFileFound(true);
            // response->makeAnswer(response->getFileFound());
            std::cout << response->makeAnswer(response->getFileFound()) << std::endl;
            answer = response->makeAnswer(response->getFileFound());
            // fputs ("fopen example",pFile);
            fclose (pFile);
        }
        else {
            answer = response->makeAnswer(response->getFileFound());
            std::cout << response->makeAnswer(response->getFileFound()) << std::endl;
        }
    }

    std::string Processor::getAnswer() {
        return (answer);
    }

Processor::~Processor() {}
