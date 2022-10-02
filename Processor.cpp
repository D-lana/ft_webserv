#include "Processor.hpp"

Processor::Processor(std::string& _url, std::string& _root) {

     std::cout << "processor ROOT" << _root << "\n";
     std::cout << "processor url" << _url << "\n";

    pFile = NULL;
    path = ""; ////////////!!!!!!!!!!!!!!!!!!!!!!!!!!
    url = _url;
    newUrl = path.append(url);
    std::cout << "processor newurl" << newUrl << "\n";
    answer = "";


    // std::cout << "Url " << url << std::endl;
    // std::cout << "newUrl " << newUrl << std::endl;


}

    void Processor::checkFile(bool cgi_request) {
        char arr[newUrl.length() + 1];
        memset (arr, 0, (newUrl.length() + 1));
        strcpy(arr, newUrl.c_str());
         std::cout << "NEWURLLLL processor " << newUrl << "\n";
         std::cout << "ARR processor " << arr << "\n"; 
        Response *response = new Response(url);
        pFile = fopen(arr, "r");
        // unsigned long size = 0;
         std::cout << "cgi_request|||||||||||| " << cgi_request << arr << "\n"; 
        if (cgi_request == true) {
            answer = response->makeAnswer(newUrl, 100);
            //fclose (pFile);
        }  
        else if (pFile!=NULL)
        {
            // response->setFileFound(true);
            // response->makeAnswer(response->getFileFound());
            //std::cout << response->makeAnswer(response->getFileFound(), newUrl) << std::endl;
            answer = response->makeAnswer(newUrl, 200);
            fclose (pFile);

            // response->setFileFound(false); // нужно ли???
        }
        else {
            // response->setFileFound(false);
            answer = response->makeAnswer(newUrl, 404);
           // std::cout << response->makeAnswer(response->getFileFound(), newUrl) << std::endl;
        }

        delete response;
    }

    void Processor::checkPostReq(bool cgi_request) {

        if (cgi_request == true) {
            Response *response = new Response(url);
            answer = response->makeAnswer(newUrl, 100);

            delete response;
        }
        // Response *response = new Response(url);
        // answer = response->makeAnswer(newUrl, 200);

        // delete response;

    }

    void Processor::makeFile() {

        std::ofstream fout;
       // fout.open(url)

    }

    std::string Processor::getAnswer() {
        
        return (answer);
    }

Processor::~Processor() {

}