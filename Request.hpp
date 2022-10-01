#ifndef REQUESR_HPP
# define REQUESR_HPP

# include "Processor.hpp"
# include "Response.hpp"
# include "CGI.hpp"
# include <string>
# include <map>
# include <iostream>
# include <fstream>
# include <iterator>
# include <cstdlib>

class Request {

private:
    CGI cgi;
    std::string method;
    std::string buffer;
    std::string url;
    std::string protocol;
    std::string fullBuffer;
    std::map<std::string, std::string> headers;
    Processor *proc1;
    bool parsLine;
    bool parsHeaders;
    std::string boundary;
    std::string endBoundary;
    std::string filename;
    bool endBody;
    // std::map<std::string, std::string> bodyData;

public:
    Request(std::string& _buffer);
    ~Request();
    void makeHeaders();
    void parsFirstLine();
    Processor *getProcessor();
    void setBuffer(std::string& _buffer);
    void requestParsing();
    void bodyParsing();
    void makeFullBuffer();
    bool getEndBody();
    // void bodyParsingToFile();

};

#endif