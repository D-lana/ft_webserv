#include "Http.hpp"

Http::Http(int _fd, std::string& _buffer) {

    fd = _fd;
   buffer = _buffer;

    request = new Request(buffer);
}

Http::Http() {

}

Http::~Http() {
    delete request;
}

Request *Http::getRequest() {
    return (request);
}

std::string Http::getPartAnswer() {
    std::string partAnswer;
    Processor *proc = request->getProcessor();

    partAnswer = proc->getAnswer();
    return (partAnswer);


}