#include "Library.hpp"

Request::Request(std::string& _buffer){

	method = "";
	buffer = "";
	buffer = _buffer;
	url = "";
	protocol = "HTTP/1.1";
	fullBuffer = "";
	parsLine = false;
	parsHeaders = false;
	endBody = false;
	cgiRequest = false;
	env = new char*[COUNT_ENV];
	for(int i = 0; i < COUNT_ENV; i++) {
		env[i] = NULL;
	}
	slash = "/";
}

int Request::parsFirstLine() {

	std::size_t pos = 0;
	if ((pos = buffer.find(' ')) == std::string::npos) {
		response = new Response();
		response->makeAnswer(newUrl, 400);
		return (-1);
	}
	method = buffer.substr(0, pos);
	buffer.erase(0, pos+1);

	if ((pos = buffer.find(' ')) == std::string::npos) {
		response = new Response();
		response->makeAnswer(newUrl, 400);
		return (-1);
	}
	url = buffer.substr(1, pos - 1);	
	buffer.erase(0, pos+1);
	if ((pos = url.find(siteName)) != std::string::npos){
		std::string tmp;
		tmp = url;
		url = url.substr(0, pos);
		url = url.append(tmp.substr(pos + siteName.length()));
	}
	if ((pos = url.find(root)) != std::string::npos){
		root = "";
	}
	newUrl = root + url;
	if (url == ""){
		url = "index.html";
	}
	if ((pos = buffer.find("\r\n")) == std::string::npos) {
		response = new Response();
		response->makeAnswer(newUrl, 400);
		return (-1);
	}
	buffer.erase(0, pos + 2);
	return(0);
}

int Request::makeHeaders() {
	
	std::string tmpStr;
	std::string keyHead;
	std::string valueHead;
	std::size_t delimiter;
	std::size_t pos;

	while (buffer.compare("\r\n")) {
		if ((pos = buffer.find("\r\n")) == std::string::npos) {
			response = new Response();
			response->makeAnswer(newUrl, 400);
			return (-1);
		}
		if (pos == 0){
			break;
		}
		tmpStr = buffer.substr(0, pos);
		if ((delimiter = tmpStr.find(": ")) == std::string::npos) {
			response = new Response();
			response->makeAnswer(newUrl, 400);
			return (-1);
		}
		keyHead = tmpStr.substr(0, delimiter);
		valueHead = tmpStr.substr(delimiter + 2, tmpStr.length() - keyHead.length()-2);
		headers.insert(std::pair<std::string, std::string> (keyHead, valueHead));
		buffer.erase(0, pos+2);
	}
	if (createCGI() == -1){
		return(-1);
	}
	return(0);
}

int Request::createCGI() {
	std::size_t pos;

	if (url.find("cgi-bin") != std::string::npos) {
		std::string path_info = "PATH_INFO=" + newUrl;
		std::string request_method = "REQUEST_METHOD=";
		request_method.append(method);
		std::string query_string = "QUERY_STRING=";
		query_string.append(url);
		
		env[3] = strdup("");
		env[4] = strdup("");
		env[5] = strdup("");
		if (method == "POST") {
			std::string content_type = "CONTENT_TYPE=";
			std::map<std::string, std::string>::iterator it1 = headers.find("Content-Type");
			if (it1 == headers.end()) {
				response = new Response();
				response->makeAnswer(newUrl, 400);
				return (-1);
			}
			content_type.append(it1->second);
			std::string content_length = "CONTENT_LENGTH=";
			std::map<std::string, std::string>::iterator it2 = headers.find("Content-Length");
			if (it2 == headers.end()) {
				response = new Response();
				response->makeAnswer(newUrl, 400);
				return (-1);
			}
			content_length.append(it2->second);
			env[3] = strdup(content_type.c_str());
			env[4] = strdup(content_length.c_str());
		}
		env[0] = strdup(path_info.c_str());
		env[1] = strdup(request_method.c_str());
		env[2] = strdup(query_string.c_str());	
		if (cgi->createDynamicHtml(env, newUrl) == -1) {
			response = new Response();
			response->makeAnswer(newUrl, 404);
			return (-1);
		}
		if ((pos = url.find('.')) != std::string::npos) {
			url = url.substr(0, pos+1) + "html";
			cgiRequest = true;
		}
	}
	return(0);
}

	void Request::makeFullBuffer(){
	
		if (buffer != ""){
			fullBuffer.append(buffer);
			if (fullBuffer.find(endBoundary)!= std::string::npos) {
				if (fullBuffer.length() > _maxBodySize){
					response->makeAnswer(newUrl, 413);
				}
				endBody = true;
			}
		}
		buffer = "";
	}

	void Request::bodyParsing(){

        std::size_t pos = 0;
        while (fullBuffer.find(endBoundary) != std::string::npos){
            if ((pos = fullBuffer.find("filename=")) != std::string::npos) {
                fullBuffer.erase(0, pos+10);
                filename = fullBuffer.substr(0, fullBuffer.find("\""));
                fullBuffer.erase(0, fullBuffer.find("\r\n\r\n") + 4);
            }
            std::size_t posEof = fullBuffer.find(boundary);
            std::size_t posN = fullBuffer.rfind("\r\n", posEof);
            std::ofstream fout;
            fout.open(("site_example/upload/" + filename).c_str(), std::ofstream::out);
            fout << fullBuffer.substr(0, posN);
            fout.close();
            fullBuffer.erase(0, posEof + boundary.length());
        }
            fullBuffer = "";
     }

	int Request::requestParsing() {

		if (!parsLine) {
			parsFirstLine();
			parsLine = true;
		}
		if (!parsHeaders) {
			makeHeaders();
			parsHeaders = true;
		}
		if (findRedirection() == 302) {
			response = new Response();
			endBody = true;
			response->makeAnswer(redirect_site, 302);
			return (0);
		}
		response = new Response(url, root);
		if (!method.compare("GET")) {
			response->checkFile(cgiRequest);
			endBody = true;
		} else if (!method.compare("POST")) {
			std::map<std::string, std::string>::iterator it = headers.find("Content-Type");
			if (it == headers.end()) {
				response->makeAnswer(newUrl, 400);
			}
			std::map<std::string, std::string>::iterator it2 = headers.find("Content-Length");
			if (it2 == headers.end()) {
				response->makeAnswer(newUrl, 400);
			}	
			std::string preBoundary;
			preBoundary = it->second.substr(it->second.find("boundary=") + 9);
			boundary = preBoundary.substr(preBoundary.rfind('-') + 1);
			endBoundary = boundary + "--";
			makeFullBuffer();
			if (endBody==true){
				bodyParsing();
				response->checkPostReq(cgiRequest, filename);
				return (0);
			}
		} else if (!method.compare("DELETE")){
			response->checkFileDeleting(newUrl);
			endBody = true;
			return (0);

		} else {
			endBody = true;
			response->makeAnswer(newUrl, 501);
			return (-1);
		}
	return (0);
}

int Request::findRedirection() {
	redirect_code = redirect_name = redirect_site = "";
	for (std::vector<Location>::iterator it = vecLocation.begin(); it != vecLocation.end(); ++it) {
		if (it->getLocationRedirection() == true) {
			redirect_code = it->getLocationIndex();
			redirect_name = it->getLocationName();
			redirect_site = it->getRedirectionSite();
			if (url == redirect_name || slash + url == redirect_name) {
				return (302);
			}
		}
	}
	return (0);
}

Request::~Request(){
	delete response;
}

Response* Request::getResponse() {
	return (response);
}

void Request::setBuffer(std::string& _buffer) {
	buffer = "";
	buffer = _buffer;
}

bool Request::getEndBody(){
	return (endBody);
}

void Request::setRoot(const std::string& _root){
	root = _root;
}

const std::string Request::getRoot() const {
	return(root);
}

void Request::setSiteName(const std::string& _siteName) {
   siteName = _siteName; 
}
void Request::setUpload(const std::string& _upload){
	upload = _upload;
}

void Request::setMaxBodySize(const size_t &maxBodySize) {
	_maxBodySize = maxBodySize;
}

void Request::setLocation(std::vector<Location> &_vecLocation) {
	vecLocation = _vecLocation;
}
