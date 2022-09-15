#ifndef REQSPONSE_HPP
# define REQSPONSE_HPP

# include "Processor.hpp"
# include <string>
# include <iostream>
# include <sstream>
# include <fstream>
# include <map>
# include <vector>


class Response {
    private:
        bool fileFound;
        std::string answer;
        std::map<std::string, std::string> mimeType;
        std::map<std::string, std::string> codeStatus;
        std::string protocol;
        std::string contentType;
        std::string contentLength;
        std::string url;

        std::stringstream response; // сюда будет записываться ответ клиенту
        std::stringstream response_body; // тело ответа

    public:
        Response(std::string url);
        ~Response();
        bool getFileFound();
        void setFileFound(bool _fileFound);

        std::string makeAnswer(bool _fileFound, std::string newUrl);
        void initMimeType();
        // void initCodeStatus();
        std::string findContentType();

};



#endif