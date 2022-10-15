#ifndef HTTP_HPP
# define HTTP_HPP

# include "Library.hpp"

class Http {

    private:
        std::map<int, Request*> requests;
        size_t contentSize;
        bool endAnswer;

    public:

        Http();
        ~Http();

        Request* getRequest(int fd);
        std::string getPartAnswer(int fd);
        int initRequest(int _fd, std::string _buffer, ServerPairs &servPairs);
        size_t getContentSize();
        bool getEndAnswer();
        void deleteRequest(int fd);
};

#endif
