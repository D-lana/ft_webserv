#include "Library.hpp"

Http::Http() {
    endAnswer = false;
}

Http::~Http() {}

Request *Http::getRequest(int fd) {
    std::map<int, Request*>::iterator it = requests.find(fd);
    return (it->second);
}

std::string Http::getPartAnswer(int fd) {
    std::string partAnswer;
    std::string fullAnswer;
    endAnswer = false;
    contentSize = getRequest(fd)->getResponse()->getContentSize();
    fullAnswer = getRequest(fd)->getResponse()->getAnswer();
    if (fullAnswer.length() > BUFSIZE) {
        partAnswer = fullAnswer.substr(0, BUFSIZE);
    } else {
        endAnswer = true;
        return (fullAnswer);
    }
    if (getRequest(fd)->getResponse()->cutAnswer() == 0) {
        endAnswer = true;
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
        request->setSiteName(servPairs.getServName());
        request->setUpload(servPairs.getUpload());
        request->setLocation(servPairs.getLocations());
        request->requestParsing();
        return(request->getEndBody());
    } else {
        it->second->setBuffer(_buffer);
        it->second->requestParsing();
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
    if (it != requests.end()){
        requests.erase(it);
    }
}
