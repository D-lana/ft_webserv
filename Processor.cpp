#include "Processor.hpp"

Processor::Processor(std::string _url) {

    path = "resources";
    url = _url;
    newUrl = path.append(url);


    std::cout << "Url " << url << std::endl;
    std::cout << "newUrl " << newUrl << std::endl;


}


// std::string Processor::checkFile() {
    void Processor::checkFile() {
        char arr[newUrl.length() + 1];
        strcpy(arr, newUrl.c_str());
        Response *response = new Response(url);
        pFile = fopen(arr, "r");
        // unsigned long size = 0;
        

        if (pFile!=NULL)
        {
            response->setFileFound(true);
            // response->makeAnswer(response->getFileFound());
            std::cout << response->makeAnswer(response->getFileFound(), newUrl) << std::endl;
            answer = response->makeAnswer(response->getFileFound(), newUrl);
            // fputs ("fopen example",pFile);
            fclose (pFile);
        }
        else {
            response->setFileFound(false);
            answer = response->makeAnswer(response->getFileFound(), newUrl);
            std::cout << response->makeAnswer(response->getFileFound(), newUrl) << std::endl;
        }



        
    }

    std::string Processor::getAnswer() {
        return (answer);
    }

Processor::~Processor() {}