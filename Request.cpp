#include "Request.hpp"

Request::Request(std::string& buffer){

    parsLine = false;
    parsHeaders = false;

    // std::string str(_buffer);
    std::size_t pos;

    if (!parsLine) {
        // std::cout << "buffer " << "|" << buffer << "|" << std::endl;
        if ((pos = buffer.find(' ')) == std::string::npos) {
            std::cout << "Request.cpp, p. 8 - symbol not found" << std::endl;  // переделать
            exit(-1);
        }
        
        method = buffer.substr(0, pos);
        std::cout << "method" << "|" << method << "|" << std::endl;
        buffer.erase(0, pos+1);
        if ((pos = buffer.find(' ')) == std::string::npos) {
            std::cout << "Request.cpp, p. 16 - symbol not found" << std::endl;  // переделать
            exit(-1);
        }
        url = buffer.substr(1, pos - 1);
        buffer.erase(0, pos+1);
        if ((pos = buffer.find("\r\n")) == std::string::npos) {
            std::cout << "Request.cpp, p. 22 - symbol not found" << std::endl;  // переделать
            exit(-1);
        }

        protocol = "HTTP/1.1";
        buffer.erase(0, pos + 2);
        // std::cout << "buffer " <<"|" << buffer << "|" << std::endl;
        parsLine = true;
}
    if (!parsHeaders) {
        // std::cout << "AAAAAAAAA" << std::endl;
        headers = makeHeaders(buffer);
        parsHeaders = true;
    }
    // std::cout << "buffer " <<"|" << buffer << "|" << std::endl;
    std::cout << "----------Print string -----------" << std::endl;
    // std::cout << "buffer " <<"|" << buffer << "|" << std::endl;
    std::cout << "url " << "|" << url << "|" << std::endl;

    proc1 = new Processor(url);
    if (!method.compare("GET")) {
        proc1->checkFile();
    }
    else if (!method.compare("POST")) {

        std::map<std::string, std::string>::iterator it = headers.find("Content-Type");
        if (it == headers.end()) {
            std::cout << "ContentType not found" << std::endl; // убрать
        }
        std::string preBoundary;
        preBoundary = it->second.substr(it->second.find("boundary=") + 9);
        std::cout << "preBoundary |" << preBoundary << "|" << std::endl;
        boundary = preBoundary.substr(preBoundary.rfind('-') + 1);
        std::cout << "boundary |" << boundary << "|" << std::endl;


        //proc1->checkFile();
    }
    
    std::cout << "----------Print map-----------" << std::endl;
    std::map<std::string, std::string>::iterator it = headers.begin();
    for (int i = 0; it != headers.end(); it++, i++) {
        std::cout << "|" << it->first << "|" << it->second << "|"<< std::endl;
    }
    std::cout << "---------End printing--------" << std::endl;
}

 std::map<std::string, std::string> Request::makeHeaders(std::string& str)
{
    std::string tmpStr;
    std::string keyHead;
    std::string valueHead;
    std::size_t delimiter;
    std::size_t pos;
    std::map<std::string, std::string> _headers;

    while (str.compare("\r\n")) {
        if ((pos = str.find("\r\n")) == std::string::npos) {
            std::cout << "Request.cpp, p. 61 - symbol not found" << std::endl;  // переделать
            exit(-1);
        }
        // std::cout << "pos " << pos << std::endl;
        tmpStr = str.substr(0, pos);
        if ((delimiter = tmpStr.find(": ")) == std::string::npos) {
            // std::cout << "Request.cpp, p. 68 - symbol not found" << std::endl;  // переделать
            break;
            // exit(-1);
        }
        keyHead = tmpStr.substr(0, delimiter);
        valueHead = tmpStr.substr(delimiter + 2, tmpStr.length() - keyHead.length()-2);
        _headers.insert(std::pair<std::string, std::string> (keyHead, valueHead));
        str.erase(0, pos+2);
        // str = "";
    }
    return (_headers);
}

Request::~Request(){
    delete proc1;
}

Processor *Request::getProcessor() {
    return (proc1);
}