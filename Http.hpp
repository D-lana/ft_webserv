#ifndef HTTP_HPP
# define HTTP_HPP

# include "Request.hpp"
# include <string>
# include <map>

class Http {

    private:
        // int fd = 0;
        // std::string buffer;
        // Request *request;
        
        std::map<int, Request*> requests;
        size_t contentSize; // временно????
        // Processor *answer;
        bool endAnswer;

    public:

        Http();
        // Http(int _fd, std::string& _buffer);

        ~Http();

        Request* getRequest(int fd);
        std::string getPartAnswer(int fd);
        bool initRequest(int _fd, std::string _buffer, std::string _root);
        size_t getContentSize();
        void setEndAnswer(bool ehdAn); // временно
        void deleteRequest(int fd);
};



#endif