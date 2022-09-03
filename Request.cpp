#include "Request.hpp"

Request::Request(const char buffer[]){

    std::string str(buffer);
    std::size_t pos = str.find(' ');
    std::size_t posSlesh = str.find('/');
    std::size_t spase = 0;
    std::size_t pos2 = str.find("\r\n");
    int i = 0;
    for ( ; spase < 2; ++i){
        if (buffer[i] == ' ')
            spase++;
    }
    
    method = str.substr(0, pos);
    url = str.substr(posSlesh, i - posSlesh - 1);
    protocol = "HTTP/1.1";
    str.erase(0, pos2 + 2);
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
    // std::cout << "---------End printing--------" << std::endl;
}

 std::map<std::string, std::string> Request::makeHeaders(std::string& str)
{
    int i = 0;
    std::string tmpStr;
    std::string keyHead;
    std::string valueHead;
    std::size_t delimiter;
    std::map<std::string, std::string> _headers;

    while (str.compare("\r\n")) {
        std::size_t pos = str.find("\r\n");
        tmpStr = str.substr(0, pos);
        delimiter = tmpStr.find(": ");
        keyHead = tmpStr.substr(0, delimiter);
        valueHead = tmpStr.substr(delimiter + 2, tmpStr.length() - keyHead.length()-2);
        _headers.insert(std::pair<std::string, std::string> (keyHead, valueHead));
        str.erase(0, pos+2);
    }
    return (_headers);
}

Request::~Request(){}

Processor *Request::getProcessor() {
    return (proc1);
}