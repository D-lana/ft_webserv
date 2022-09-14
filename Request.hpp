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
    std::string url;
    std::string protocol;
    std::map<std::string, std::string> headers;
    Processor *proc1;
    bool parsLine;
    bool parsHeaders;
    std::string boundary;

public:
    Request(const char buffer[]);
    ~Request();
    std::map<std::string, std::string> makeHeaders(std::string& str);
    Processor *getProcessor();
};

#endif