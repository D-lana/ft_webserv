#include "Library.hpp"

Http::Http() {
    endAnswer = false;
}

Http::~Http() {
    
}

Request *Http::getRequest(int fd) {
    std::map<int, Request*>::iterator it = requests.find(fd);
    return (it->second);
}

std::string Http::getPartAnswer(int fd) {
    std::string partAnswer;
    std::string fullAnswer;
    endAnswer = false;
    // Processor *proc = getRequest(fd)->getProcessor();
    contentSize = getRequest(fd)->getResponse()->getContentSize(); // убрать
    fullAnswer = getRequest(fd)->getResponse()->getAnswer();
    std::cout << "------http contentSize--------" << getRequest(fd)->getResponse()->getContentSize() << std::endl;
    std::cout << "\x1b[1;90m" << "\n> Size answer: " << fullAnswer.length() << "\n\n" << "\x1b[0m";
    if (fullAnswer.length() > BUFSIZE) {
        partAnswer = fullAnswer.substr(0, BUFSIZE);
    } else {
        endAnswer = true;
        std::cout << "\x1b[1;90m" << "\n> fullAnswer.length() < BUFSIZE 22 http" << "\n\n" << "\x1b[0m"; 
        return (fullAnswer);
    }
    if (getRequest(fd)->getResponse()->cutAnswer() == 0) {
        endAnswer = true;
        std::cout << "\x1b[1;90m" << "\n> cutAnswer() true 34 http" << "\n\n" << "\x1b[0m";
    }
    return (partAnswer);
}

int Http::initRequest(int _fd, std::string _buffer, ServerPairs &servPairs) {

    std::map<int, Request*>::iterator it = requests.find(_fd);
    if (it == requests.end()) {
        Request *request = new Request(_buffer);
        requests.insert(std::pair<int, Request*>(_fd, request));
        request->setRoot(servPairs.getRoot());
        request->setMaxBodySize(servPairs.getBodySize());
        std::cout << "servPairs.getServName()" << servPairs.getServName() << "|" << std::endl;
        request->setSiteName(servPairs.getServName());
        request->setUpload(servPairs.getUpload());
        request->setLocation(servPairs.getLocations());
        std::cout << "QQQQQQQQ"  << "|" << std::endl;
        request->requestParsing();
        std::cout << "WWWWWWW"  << "|" << std::endl;
        // if (request->requestParsing() == -1 && it->second->getEndBody() == true){
        //     return(404);
        // }
        std::cout << "it->second->getEndBody() http 52|" << request->getEndBody() << "|" << std::endl;
        return(request->getEndBody());
    } else {
        it->second->setBuffer(_buffer);
        it->second->requestParsing();
        // if(it->second->requestParsing() == -1 && it->second->getEndBody() == true){
        //     return(404);
        // }
        std::cout << "it->second->getEndBody() http 57|" << it->second->getEndBody() << "|" << std::endl;
        return(it->second->getEndBody());
    }
    return(0);
}

size_t Http::getContentSize() {
        return (contentSize);
    }

bool Http::getEndAnswer(){
    return(endAnswer);
}

void Http::deleteRequest(int fd){
    std::map<int, Request*>::iterator it = requests.find(fd);
    if (it == requests.end()){
        std::cout << "no request" << std::endl;
    } else {
        requests.erase(it);
        std::cout << "Request " <<fd << " was deleted" << std::endl;
    }

}

// size_t Http::getLenAnswer(int fd){
//         return (getRequest(fd)->getResponse()->getAnswer().length());
// }
