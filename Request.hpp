#ifndef REQUESR_HPP
# define REQUESR_HPP

# include "Processor.hpp"
# include "Response.hpp"
# include <string>
# include <map>
# include <iostream>
# include <iterator>

class Request {

private:
    std::string method;
    std::string buffer;
    std::string url;
    std::string protocol;
    std::map<std::string, std::string> headers;
    Processor *proc1;
    bool parsLine;
    bool parsHeaders;
    std::string boundary;

public:
    Request(std::string& _buffer);
    ~Request();
    std::map<std::string, std::string> makeHeaders();
    void parsFirstLine();
    Processor *getProcessor();
    void setBuffer(std::string& _buffer);
};

#endif