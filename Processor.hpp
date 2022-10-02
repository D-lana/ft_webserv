#ifndef PROCESSOR_HPP
# define PROCESSOR_HPP

# include "Response.hpp"
# include <cstdio>
# include <string>
# include <iostream>
# include <cstring>
# include <fstream>


class Processor {

private:
    FILE *pFile;
    std::string path;
    std::string url;
    std::string newUrl;
    std::string answer;
    // Response *response;

public:
    Processor(std::string& url, std::string& _root);
   ~Processor();
    // std::string checkFile();
    void checkFile(bool cgi_request);
    void makeFile();
    void checkPostReq(bool cgi_request); // ????

    std::string getAnswer();
};

#endif