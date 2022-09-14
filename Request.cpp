#include "Request.hpp"

Request::Request(const char buffer[]){

    std::string str(buffer);
    std::size_t pos;

    if ((pos = str.find(' ')) == std::string::npos) {
        std::cout << "Request.cpp, p. 9 - symbol not found" << std::endl;  // переделать
        exit(-1);
    }
    // if ((posSlesh = str.find('/')) == std::string::npos) {
    //     std::cout << "Request.cpp, p. 12 - symbol not found" << std::endl;  // переделать
    //     exit(-1);
    // }
    // std::size_t spase = 0;
    // if ((pos2 = str.find("\r\n")) == std::string::npos) {
    //     std::cout << "Request.cpp, p. 18 - symbol not found" << std::endl;  // переделать
    //     exit(-1);
    // }
    // int i = 0;
    // for ( ; spase < 2; ++i){
    //     if (buffer[i] == ' ')
    //         spase++;
    // }
    
    method = str.substr(0, pos);
    std::cout << "method" << "|" << method << "|" << std::endl;
    str.erase(0, pos+1);
    if ((pos = str.find(' ')) == std::string::npos) {
        std::cout << "Request.cpp, p. 30 - symbol not found" << std::endl;  // переделать
        exit(-1);
    }
    url = str.substr(1, pos - 1);
    str.erase(0, pos+1);
    if ((pos = str.find("\r\n")) == std::string::npos) {
        std::cout << "Request.cpp, p. 36 - symbol not found" << std::endl;  // переделать
        exit(-1);
    }
    // url = str.substr(posSlesh, i - posSlesh - 1);
    // url = str.substr(posSlesh, i - 1);
    protocol = "HTTP/1.1";
    str.erase(0, pos + 2);
    
    headers = makeHeaders(str);

    std::cout << "----------Print string -----------" << std::endl;
    std::cout << "|" << url << "|" << std::endl;

    proc1 = new Processor(url);
    proc1->checkFile();
    
    // std::cout << "----------Print map-----------" << std::endl;
    // std::map<std::string, std::string>::iterator it = headers.begin();
    // for (int i = 0; it != headers.end(); it++, i++) {
    //     std::cout << "|" << it->first << "|" << it->second << "|"<< std::endl;
    // }
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

    while (!str.compare("\r\n")) {
        if ((pos = str.find("\r\n")) == std::string::npos) {
            std::cout << "Request.cpp, p. 58 - symbol not found" << std::endl;  // переделать
            exit(-1);
        }
        // std::cout << "pos " << pos << std::endl;
        tmpStr = str.substr(0, pos);
        // std::cout << "tmpStr " << tmpStr << std::endl;
        if ((delimiter = tmpStr.find(": ")) == std::string::npos) {
            std::cout << "Request.cpp, p. 65 - symbol not found" << std::endl;  // переделать
            exit(-1);
        }
        keyHead = tmpStr.substr(0, delimiter);
        valueHead = tmpStr.substr(delimiter + 2, tmpStr.length() - keyHead.length()-2);
        _headers.insert(std::pair<std::string, std::string> (keyHead, valueHead));
        str.erase(0, pos+2);
    }
    return (_headers);
}

Request::~Request(){
    delete proc1;
}

Processor *Request::getProcessor() {
    return (proc1);
}