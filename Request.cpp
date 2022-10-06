#include "Request.hpp"

Request::Request(std::string& _buffer){

    // method = "";
    // buffer = "";
    buffer = _buffer;
    // url = "";
    protocol = "HTTP/1.1";
    fullBuffer = "";
    parsLine = false;
    parsHeaders = false;
    endBody = false;
    cgiRequest = false;
    std::cout << "15 request root" << "|" << root << "|" << std::endl;
}

void Request::parsFirstLine() {

    std::size_t pos = 0;
    // std::cout << "buffer " << "|" << buffer << "|" << std::endl;
    method = "";
    if ((pos = buffer.find(' ')) == std::string::npos) {
        std::cout << "Request.cpp, p. 8 - symbol not found" << std::endl;  // переделать
        exit(-1);
    }
    method = buffer.substr(0, pos);
    std::cout << "method" << "|" << method << "|" << std::endl;
    buffer.erase(0, pos+1);

    url = "";
    if ((pos = buffer.find(' ')) == std::string::npos) {
        std::cout << "Request.cpp, p. 16 - symbol not found" << std::endl;  // переделать
        exit(-1);
    }
    url = buffer.substr(1, pos - 1);
    if (url == ""){
        url = "index.html";
    }
    std::cout << "url " << "|" << url << "|" << std::endl;
    buffer.erase(0, pos+1);

    // if (url.find("cgi-bin") != std::string::npos) {
    //     cgi->createDynamicHtml(url);
    //     if ((pos = url.find('.')) != std::string::npos) {
    //         url = url.substr(0, pos+1) + "html";
    //         std::cout << "url BIN " << "|" << url << "|" << std::endl;
    //             cgiRequest = true;
    //     }
    // }

    if ((pos = buffer.find("\r\n")) == std::string::npos) {
        std::cout << "Request.cpp, p. 22 - symbol not found" << std::endl;  // переделать
        exit(-1);
    }
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
                std::cout << "Request.cpp, p. 67 - symbol not found" << std::endl;  // переделать
                exit(-1);
            }
            // std::cout << "pos " << pos << std::endl;
            tmpStr = buffer.substr(0, pos);
            if ((delimiter = tmpStr.find(": ")) == std::string::npos) {
                // std::cout << "Request.cpp, p. 68 - symbol not found" << std::endl;  // переделать
                break;
            }
            keyHead = tmpStr.substr(0, delimiter);
            valueHead = tmpStr.substr(delimiter + 2, tmpStr.length() - keyHead.length()-2);
            headers.insert(std::pair<std::string, std::string> (keyHead, valueHead));
            buffer.erase(0, pos+2);
           
            // std::cout << "buffer0 |" << buffer << "|" << std::endl;
        }
    }

    void Request::makeFullBuffer(){

        std::map<std::string, std::string>::iterator it = headers.find("Content-Length");
        if (it == headers.end()) {
            std::cout << "Content Length not found" << std::endl; // убрать
        }
        if (buffer != ""){
            fullBuffer.append(buffer);
            if (fullBuffer.find(endBoundary)!= std::string::npos) {
                endBody = true;
            }
        }
        // std::cout << "FullBuffer |" << fullBuffer << "|" <<std::endl;
        buffer = "";
    }

    void Request::bodyParsing(){

        std::size_t pos = 0;
        while (fullBuffer.find(endBoundary) != std::string::npos){
            if ((pos = fullBuffer.find("filename=")) != std::string::npos) {
                fullBuffer.erase(0, pos+10);
                filename = fullBuffer.substr(0, fullBuffer.find("\""));
                std::cout << "body parsing filename |" << filename << "|" <<std::endl;
                fullBuffer.erase(0, fullBuffer.find("\r\n\r\n") + 4);
            // } else {
            //     // filename = "cats.gif";
            //     std::cout << "-------NO NAME--------" <<std::endl;
            //     exit(-1);
            }
            std::size_t posEof = fullBuffer.find(boundary);
            std::size_t posN = fullBuffer.rfind("\r\n", posEof);

            std::cout << "----------request file open---------" <<std::endl;
            std::ofstream fout;
            fout.open("site_example/cgi-bin/upload/" + filename, std::ofstream::out);
            // fout.open("upload/" + filename, std::ofstream::out);
            // std::size_t posEof = fullBuffer.find(boundary);
            // std::size_t posN = fullBuffer.rfind("\n", posEof);
           
            // fout << fullBuffer.substr(0, posN-1);
            fout << fullBuffer.substr(0, posN);
            
            fout.close();
            std::cout << "----------request file closed---------" <<std::endl;
            fullBuffer.erase(0, posEof + boundary.length());
           
            std::cout << "END BODY PARSING" << std::endl;
        }
            fullBuffer = "";
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
        // std::cout << "----------Print map-----------" << std::endl;
        // std::map<std::string, std::string>::iterator it = headers.begin();
        // for (int i = 0; it != headers.end(); it++, i++) {
        //     std::cout << "|" << it->first << "|" << it->second << "|"<< std::endl;
        // }
        // std::cout << "---------End printing--------" << std::endl;
        
        std::cout << "156 request ROOT" << root << "|" << std::endl;
        std::cout << "157 request url " << url << "|" << std::endl;

        response = new Response(url, root);
        if (!method.compare("GET")) {
            // response = new Response(url, root);
            response->checkFile(cgiRequest); // CGI проверить нужен ли он тут вообще
            endBody = true;
            // parsLine = false; // убрать после обработки удаления запросов
            // parsHeaders = false; // убрать после обработки удаления запросов
        } else if (!method.compare("POST")) {
            // response = new Response(url, root);
            std::map<std::string, std::string>::iterator it = headers.find("Content-Type");
            if (it == headers.end()) {
                std::cout << "ContentType not found" << std::endl; // убрать
            }
            std::string preBoundary;
            preBoundary = it->second.substr(it->second.find("boundary=") + 9);
            boundary = preBoundary.substr(preBoundary.rfind('-') + 1);
            endBoundary = boundary + "--";

            makeFullBuffer();
            if (endBody==true){
                bodyParsing();
                std::cout << "request filename |" << filename << "|" << std::endl; 
                response->checkPostReq(cgiRequest, filename);
                // parsLine = false;
                // parsHeaders = false;
            }
            
        } else if (!method.compare("DELETE")){
            // response = new Response(url, root);
            remove(root.append(url).c_str());
            std::cout << "----------DELETE-----------" << std::endl;

        } else {
            // response = new Response(url, root);
            std::cout << "UNDEFINED 405 — Method Not Allowed" << std::endl;
        }
        // delete response;
        // method = "";
        // url = "";
    
}

Request::~Request(){
    // delete proc1;
}

Response* Request::getResponse() {
    return (response);
}

void Request::setBuffer(std::string& _buffer) {
    buffer = "";
    buffer = _buffer;
}

bool Request::getEndBody(){
    return (endBody);
}

void Request::setRoot(std::string& _root){
    root = _root;
}

const std::string Request::getRoot() const {
    return(root);
}

// void setFilename(std::string _filename){

// }