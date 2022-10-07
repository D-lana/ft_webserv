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

    bool parsLine;
    bool parsHeaders;
    bool cgiRequest;
    bool endBody;

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
    // void setFilename(std::string _filename);
    const std::string getRoot() const;

};

#endif
