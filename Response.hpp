#ifndef REQSPONSE_HPP
# define REQSPONSE_HPP

# include "Processor.hpp"
# include <string>
# include <iostream>
# include <sstream>
# include <fstream>
# include <map>
# include <vector>

#define READ_BUFSIZE 1000


class Response {
    private:
        // bool fileFound;
        std::string answer;
        std::map<std::string, std::string> mimeType;
        std::map<std::string, std::string> codeStatus;
        std::string protocol;
        std::string contentType;
        std::string contentLength;
        std::string url;
    

        int streamPos = 0;

        std::stringstream response; // сюда будет записываться ответ клиенту
        std::stringstream response_body; // тело ответа

    public:
        Response(std::string url);
        ~Response();
        // bool getFileFound();
        // void setFileFound(bool _fileFound);

        std::string makeAnswer(std::string newUrl, int code);
        void initMimeType();
        // void initCodeStatus();
        std::string findContentType();

};



#endif