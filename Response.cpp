#include "Response.hpp"

 Response::Response(){
     fileFound = false;

 }
Response::~Response() {

}

bool Response::getFileFound() {
    return(fileFound);
}

void Response::setFileFound(bool _fileFound) {
    fileFound = _fileFound;
}

std::string Response::makeAnswer(bool _fileFound) {

    if (_fileFound) {
        answer = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 22\n\nHello World! tra-ta-ta";
    }
    else {
        answer = "404 file not found";
    }

    return(answer);
}