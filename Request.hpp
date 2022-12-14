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
    std::string redirect_code; 
	std::string redirect_name; 
	std::string redirect_site;
    std::string slash;

    size_t _maxBodySize;

    bool parsLine;
    bool parsHeaders;
    bool cgiRequest;
    bool endBody;

    char** env;

    std::map<std::string, std::string> headers;
    std::vector<Location> vecLocation;

public:
    Request(std::string& _buffer);
    ~Request();
    int makeHeaders();
    int parsFirstLine();
    int requestParsing();
    void bodyParsing();
    void makeFullBuffer();
    bool getEndBody();
    Response* getResponse();
    void setBuffer(std::string& _buffer);
    void setRoot(const std::string& _root);
    void setSiteName(const std::string& _siteName);
    void setUpload(const std::string& _upload);
    const std::string getRoot() const;
    void setMaxBodySize(const size_t &maxBodySize);
    int createCGI();
    void setLocation(std::vector<Location> &_vecLocation);
    int findRedirection();
};

#endif
