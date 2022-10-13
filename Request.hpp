#ifndef REQUESR_HPP
# define REQUESR_HPP

# include "Library.hpp"

class Request {

private:
    CGI *cgi;
    Response *response;

    std::string method;
    std::string buffer;
    std::string url;
    std::string protocol;
    std::string fullBuffer;
    std::string boundary;
    std::string endBoundary;
    std::string filename;
    std::string root;
    std::string newUrl;
    std::string siteName;
    std::string upload;

    size_t _maxBodySize;

    bool parsLine;
    bool parsHeaders;
    bool cgiRequest;
    bool endBody;

    char** env;

    std::map<std::string, std::string> headers;

public:
    Request(std::string& _buffer);
    ~Request();
    void makeHeaders();
    void parsFirstLine();
    void requestParsing();
    void bodyParsing();
    void makeFullBuffer();
    bool getEndBody();
    Response* getResponse();
    void setBuffer(std::string& _buffer);
    void setRoot(const std::string& _root);
    void setSiteName(const std::string& _siteName);
    void setUpload(const std::string& _upload);
    // void setFilename(std::string _filename);
    const std::string getRoot() const;
    void setMaxBodySize(const size_t &maxBodySize);

};

#endif
