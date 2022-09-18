#ifndef HTTP_HPP
# define HTTP_HPP

# include "Request.hpp"
# include <string>

class Http {

    private:
        int fd;
        std::string buffer;
        Request *request;
        // Processor *answer;



    public:
        Http(int _fd, std::string& _buffer);
        Http();
        ~Http();

        Request* getRequest();
        std::string getPartAnswer();


};



#endif