#ifndef HTTP_HPP
# define HTTP_HPP

# include "Library.hpp"

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
        int initRequest(int _fd, std::string _buffer, ServerPairs &servPairs);
        size_t getContentSize();
        bool getEndAnswer();
        void deleteRequest(int fd);
        //size_t getLenAnswer(int fd);


};

#endif
