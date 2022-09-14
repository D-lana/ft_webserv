#include "Processor.hpp"

Processor::Processor(std::string& _url) {

    pFile = NULL;
    path = "resources/";
    url = _url;
    newUrl = path.append(url);
    answer = "";


    std::cout << "Url " << url << std::endl;
    std::cout << "newUrl " << newUrl << std::endl;


}

    void Processor::checkFile() {
        char arr[newUrl.length() + 1];
        memset (arr, 0, (newUrl.length() + 1));
        strcpy(arr, newUrl.c_str());
        Response *response = new Response(url);
        pFile = fopen(arr, "r");
        // unsigned long size = 0;
        
        if (pFile!=NULL)
        {
            response->setFileFound(true);
            // response->makeAnswer(response->getFileFound());
            //std::cout << response->makeAnswer(response->getFileFound(), newUrl) << std::endl;
            answer = response->makeAnswer(response->getFileFound(), newUrl);
            fclose (pFile);
            response->setFileFound(false); // нужно ли???
        }
        else {
            response->setFileFound(false);
            answer = response->makeAnswer(response->getFileFound(), newUrl);
           // std::cout << response->makeAnswer(response->getFileFound(), newUrl) << std::endl;
        }

        delete response;
    }

    std::string Processor::getAnswer() {
        return (answer);
    }

Processor::~Processor() {}