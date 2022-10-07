#include "Http.hpp"

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

bool Http::initRequest(int _fd, std::string _buffer, ServerPairs &servPairs) {

    std::map<int, Request*>::iterator it = requests.find(_fd);
    if (it == requests.end()) {
        Request *request = new Request(_buffer);
        requests.insert(std::pair<int, Request*>(_fd, request));
        // std::cout << "_root p31 |" << _root << "|" << std::endl;
        request->setRoot(servPairs.getRoot());
        //  std::cout << "root http p32 |" << request->getRoot() << "|" << std::endl;
        request->requestParsing();
        return(request->getEndBody());
    } else {
        it->second->setBuffer(_buffer);
        it->second->requestParsing();
        return(it->second->getEndBody());
    } 
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
