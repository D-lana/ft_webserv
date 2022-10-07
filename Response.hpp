#ifndef REQSPONSE_HPP
# define REQSPONSE_HPP

# include "Library.hpp"

class Response {
    private:
        std::string answer;
        std::string protocol;
        std::string contentType;
        std::string contentLength;
        std::string url;
        std::string root;
        std::string newUrl;
        std::string filename;
        std::stringstream response; // сюда будет записываться ответ клиенту
        std::stringstream response_body; // тело ответа
        FILE *pFile;
        size_t contentSize; // временно

        // int streamPos;
        std::map<std::string, std::string> mimeType;
        std::map<std::string, std::string> codeStatus;

    public:
        Response(std::string& url, std::string& _root);
        ~Response();

        std::string makeAnswer(std::string& newUrl, int code);
        std::string findContentType();
        std::string& getAnswer();
        // void setAnswer(std::string _answer);
        // void initCodeStatus();
        void initMimeType();
        void checkFile(bool cgi_request);
        void checkPostReq(bool cgi_request, std::string& filename);
        size_t getContentSize();
        size_t cutAnswer();
};

#endif
