#include "Library.hpp"

Request::Request(std::string& _buffer){

    method = "";
    buffer = "";
    buffer = _buffer;
    url = "";
    protocol = "HTTP/1.1";
    fullBuffer = "";
    parsLine = false;
    parsHeaders = false;
    endBody = false;
    cgiRequest = false;
    std::cout << "15 request root" << "|" << root << "|" << std::endl;
    env = new char*[COUNT_ENV];
	for(int i = 0; i < COUNT_ENV; i++) {
		env[i] = NULL;
	}     
}

void Request::parsFirstLine() {

    std::size_t pos = 0;
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
    newUrl = root + url;
    
    std::cout << "url " << "|" << url << "|" << std::endl;
    buffer.erase(0, pos+1);
    std::cout << "siteName req 38 " << "|" << siteName << "|" << std::endl;
    if ((pos = url.find(siteName)) != std::string::npos){
        std::string tmp;
        tmp = url;
        url = url.substr(0, pos);
        url = url.append(tmp.substr(pos + siteName.length()));

         std::cout << "url kotiki " << "|" << url << "|" << std::endl;

    }
    if ((pos = url.find(root)) != std::string::npos){
        root = "";

    }
    if (url == ""){
        url = "index.html";
    }
    // if (url.find("cgi-bin") != std::string::npos) {
    //     //////////////
    //     cgi->createDynamicHtml(newUrl);
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

        if (url.find("cgi-bin") != std::string::npos) {
        //////////////
        std::string path_info = "PATH_INFO=" + newUrl;
        std::string request_method = "REQUEST_METHOD=";
        request_method.append(method);
        std::string query_string = "QUERY_STRING=";
        query_string.append(url);

        std::string content_type = "CONTENT_TYPE="; // Content-Type -key
        std::map<std::string, std::string>::iterator it1 = headers.find("Content-Type");
        content_type.append(it1->second);
        std::string content_length = "CONTENT_LENGTH=";
        std::map<std::string, std::string>::iterator it2 = headers.find("Content-Length");
        content_length.append(it2->second); //Content-Length -key
        // std::string http_cookie = "HTTP_COOKIE=";
        // http_cookie.append(HTTP_COOKIE);

        env[0] = strdup(path_info.c_str());
        env[1] = strdup(request_method.c_str());
        env[2] = strdup(query_string.c_str());
        env[3] = strdup(content_type.c_str());
        env[4] = strdup(content_length.c_str());
        // env[5] = strdup(http_cookie.c_str());
        cgi->createDynamicHtml(env, url);
            if ((pos = url.find('.')) != std::string::npos) {
                url = url.substr(0, pos+1) + "html";
                std::cout << "url BIN " << "|" << url << "|" << std::endl;
                    cgiRequest = true;
            }
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
            fout.open(root + upload + filename, std::ofstream::out);
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
        std::cout << "----------Print map-----------" << std::endl;
        std::map<std::string, std::string>::iterator it = headers.begin();
        for (int i = 0; it != headers.end(); it++, i++) {
            std::cout << "|" << it->first << "|" << it->second << "|"<< std::endl;
        }
        std::cout << "---------End printing--------" << std::endl;
        
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
            }
            
        } else if (!method.compare("DELETE")){

            // remove((newUrl).c_str());
            // exit(0);       
            response->checkFileDeleting(newUrl);
            std::cout << "----------DELETE-----------" << std::endl;

        } else {
            response->makeAnswer(newUrl, 501);
            // std::cout << "UNDEFINED 405 — Method Not Allowed" << std::endl;
        }

    
}

Request::~Request(){
     delete response;
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

void Request::setRoot(const std::string& _root){
    root = _root;
}

const std::string Request::getRoot() const {
    return(root);
}

void Request::setSiteName(const std::string& _siteName) {
   siteName = _siteName; 
}
void Request::setUpload(const std::string& _upload){
    upload = _upload;
}