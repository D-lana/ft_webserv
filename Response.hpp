#ifndef REQSPONSE_HPP
# define REQSPONSE_HPP

# include "Processor.hpp"
# include <string>
# include <iostream>


class Response {
    private:
     bool fileFound;
     std::string answer;


    public:
        Response();
        ~Response();
        bool getFileFound();
        void setFileFound(bool _fileFound);

        std::string makeAnswer(bool _fileFound);

};



#endif