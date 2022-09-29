#include "Http.hpp"

Http::Http() {

}

Http::~Http() {
    // delete request;
}

Request *Http::getRequest(int fd) {
    std::map<int, Request*>::iterator it = requests.find(fd);
    return (it->second);
}

std::string Http::getPartAnswer(int fd) {
    std::string partAnswer;
    Processor *proc = getRequest(fd)->getProcessor();

    partAnswer = proc->getAnswer();
    return (partAnswer);


}

bool Http::initRequest(int _fd, std::string _buffer) {

    std::map<int, Request*>::iterator it = requests.find(_fd);
    if (it == requests.end()) {
        Request *request = new Request(_buffer);
        requests.insert (std::pair<int, Request*>(_fd, request));
        request->requestParsing();
        //request->getEndBody();
        return(request->getEndBody());
    } else {
        it->second->setBuffer(_buffer);
        it->second->requestParsing();
       //it->second->getEndBody();
        return(it->second->getEndBody());
    } 
}

// bool Request::getEndBody(){
//     return (endBody);
// }