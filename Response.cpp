#include "Response.hpp"

 Response::Response(std::string _url){
     fileFound = false;
     initMimeType();
     protocol = "HTTP/1.1";
     url = _url;

 }
Response::~Response() {

}

bool Response::getFileFound() {
    return(fileFound);
}

void Response::setFileFound(bool _fileFound) {
    fileFound = _fileFound;
}

std::string Response::makeAnswer(bool _fileFound, std::string newUrl) {

    if (_fileFound) {
        contentType = findContentType();


        // answer = protocol + " " + "200 OK\r\n"+ "Content-Type: " + contentType + "\r\n" + "Content-Length: 22" + "\r\n\r\n" + "Hello World! tra-la-la";
        // answer = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 22\n\nHello World! tra-la-la";

        std::string line;
        std::ifstream in(newUrl); // окрываем файл для чтения
        if (in.is_open())
        {
            while (getline(in, line))
            {
                response_body << line;
            }
        }
        in.close();     // закрываем файл

        // answer = protocol + " 200 OK\r\n"+ "Content-Type: " + contentType + "\r\n" + "Content-Length: " + contentLength + "22" + "\r\n\r\n" + "Hello World! tra-la-la";
        // std::cout << "response_body " << response_body.str()  << std::endl;

        response << protocol << " 200 OK\r\nContent-Type: " << contentType << "\r\nContent-Length: " << response_body.str().length() << "\r\n\r\n"
        << response_body.str();
        // _fileFound = false;

        answer = response.str();

        std::cout << "response" << response.str()  << std::endl;
    }
    else {
        answer = "404 file not found";
    }

    return(answer);
}

std::string Response::findContentType(){
    size_t posDot = 0;
    
    std::string key;
    posDot = url.rfind('.');
    key = url.substr(++posDot, url.length());
    std::map<std::string, std::string>::iterator it = mimeType.find(key);
    std::cout << "key = " << key << std::endl;
    std::cout << "value = " << it->second << std::endl;

    return(it->second);
}

int Response::findContentLength(){

    // int size = 0;
    return(0);
}

void Response::initMimeType() {
    mimeType["txt"]="text/plain; charset=utf-8";
    mimeType["pdf"]="application/pdf";
    mimeType["ico"]="image/x-icon";
    mimeType["cpp"]="text/x-c; charset=utf-8";
}

void Response::initCodeStatus() {
    codeStatus["200"] = "OK";
    codeStatus["403"] = "Forbidden";
    codeStatus["404"] = "Not Found";
}