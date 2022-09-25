#include "Request.hpp"

Request::Request(std::string& _buffer){

    parsLine = false;
    parsHeaders = false;
    buffer = _buffer;
    fullBuffer = "";
}

    void Request::parsFirstLine() {

        std::size_t pos = 0;

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
    }

    void Request::makeHeaders() {
        
        std::string tmpStr;
        std::string keyHead;
        std::string valueHead;
        std::size_t delimiter;
        std::size_t pos;

        while (buffer.compare("\r\n")) {
            if ((pos = buffer.find("\r\n")) == std::string::npos) {
                std::cout << "Request.cpp, p. 61 - symbol not found" << std::endl;  // переделать
                exit(-1);
            }
            // std::cout << "pos " << pos << std::endl;
            tmpStr = buffer.substr(0, pos);
            if ((delimiter = tmpStr.find(": ")) == std::string::npos) {
                // std::cout << "Request.cpp, p. 68 - symbol not found" << std::endl;  // переделать
                break;
                // exit(-1);
            }
            keyHead = tmpStr.substr(0, delimiter);
            valueHead = tmpStr.substr(delimiter + 2, tmpStr.length() - keyHead.length()-2);
            headers.insert(std::pair<std::string, std::string> (keyHead, valueHead));
            buffer.erase(0, pos+2);
           
            // std::cout << "buffer0 |" << buffer << "|" << std::endl;
        }
    }

    void Request::makeFullBuffer(){

        // bodyParsingToFile();
        // size_t len;
        std::map<std::string, std::string>::iterator it = headers.find("Content-Length");
        if (it == headers.end()) {
            std::cout << "ContentLength not found" << std::endl; // убрать
        }
        // len = (size_t)atol(it->second.c_str());
        // if (fullBuffer.length() < len){
            if (buffer != ""){
                fullBuffer.append(buffer);
                // std::cout << "cont_length " << std::atoi(it->second.c_str()) << std::endl;
                // std::cout << "length_buf " << fullBuffer.length() << std::endl;
                // std::cout << "fullBuffer |" << fullBuffer << "|" << std::endl;
        }

        buffer = "";
        // std::cout << "length " << std::atoi(it->second.c_str()) << std::endl;
    }

    void Request::bodyParsingToFile(){


        std::ofstream fout;
        fout.open("/tmp/tmpfile", std::ofstream::app);
          while (buffer != ""){
            // std::cout << "buffer2 |" << buffer << "|" << std::endl;
            fout << buffer;
            buffer.erase(0, buffer.length());
        }
        fout.close();
        // bodyParsing();

    }

    void Request::bodyParsing(){

        // std::cout << "filename |" << filename << "|" <<std::endl;

        std::size_t pos;
        while (fullBuffer.find(endBoundary) != std::string::npos){
            if ((pos = fullBuffer.find("filename=")) != std::string::npos) {
                fullBuffer.erase(0, pos+10);
                filename = fullBuffer.substr(0, fullBuffer.find("\""));
                std::cout << "filename |" << filename << "|" <<std::endl;
                fullBuffer.erase(0, fullBuffer.find("\r\n\r\n") + 4);
            }
            std::ofstream fout;
            fout.open("uploads/" + filename, std::ofstream::out);
            std::size_t posEof = fullBuffer.find(boundary);
            std::size_t posEndOfBody = fullBuffer.find("\r\n");

            fout << fullBuffer.substr(0, posEndOfBody);
            fout.close();
            fullBuffer.erase(0, posEof + boundary.length());
        }

     }

    void Request::requestParsing() {

        if (!parsLine) {
            parsFirstLine();
            parsLine = true;
        }
        if (!parsHeaders) {
            makeHeaders();
            parsHeaders = true;
        }
        std::cout << "----------Print map-----------" << std::endl;
        std::map<std::string, std::string>::iterator it = headers.begin();
        for (int i = 0; it != headers.end(); it++, i++) {
            std::cout << "|" << it->first << "|" << it->second << "|"<< std::endl;
        }
        std::cout << "---------End printing--------" << std::endl;
        
        proc1 = new Processor(url);
        if (!method.compare("GET")) {
            proc1->checkFile();
            parsLine = false;
            parsHeaders = false;
        } else if (!method.compare("POST")) {
            std::map<std::string, std::string>::iterator it = headers.find("Content-Type");
            if (it == headers.end()) {
                std::cout << "ContentType not found" << std::endl; // убрать
            }
            std::string preBoundary;
            preBoundary = it->second.substr(it->second.find("boundary=") + 9);
            boundary = preBoundary.substr(preBoundary.rfind('-') + 1);
            endBoundary = boundary + "--";

        // std::cout << "buffer body |" << buffer << "|" << std::endl;
            // bodyParsing();
            // bodyParsingToFile();
            makeFullBuffer();
            bodyParsing();
    }
}

Request::~Request(){
    delete proc1;
}

Processor *Request::getProcessor() {
    return (proc1);
}

void Request::setBuffer(std::string& _buffer) {
    // buffer = "";
    buffer = _buffer;
}