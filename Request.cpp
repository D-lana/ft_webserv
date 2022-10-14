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
	std::cout << "15 request root" << "|" << root << "|" << std::endl;
	env = new char*[COUNT_ENV];
	for(int i = 0; i < COUNT_ENV; i++) {
		env[i] = NULL;
	}
	slash = "/";
}

void Request::parsFirstLine() {

	std::size_t pos = 0;
	if ((pos = buffer.find(' ')) == std::string::npos) {
		 response = new Response();
		 std::cout  << "\x1b[1;92m" << "\n-----SMOTRI REQUEST 28 LINE!!!!!!-------\n" << "\x1b[0m";
		 response->makeAnswer(newUrl, 400);
		// std::cout << "Request.cpp, p. 8 - symbol not found" << std::endl;  // переделать
		// exit(-1);
	}
	method = buffer.substr(0, pos);
	std::cout << "method" << "|" << method << "|" << std::endl;
	buffer.erase(0, pos+1);

	if ((pos = buffer.find(' ')) == std::string::npos) {
		response = new Response();
		std::cout  << "\x1b[1;92m" << "\n-----SMOTRI REQUEST 39 LINE!!!!!!-------\n" << "\x1b[0m";
		response->makeAnswer(newUrl, 400);
		// std::cout << "Request.cpp, p. 16 - symbol not found" << std::endl;  // переделать
		// exit(-1);
	}
	url = buffer.substr(1, pos - 1);
	// newUrl = root + url;
	
	std::cout << "url " << "|" << url << "|" << std::endl;
	buffer.erase(0, pos+1);
	std::cout << "siteName req 47 " << "|" << siteName << "|" << std::endl;
	if ((pos = url.find(siteName)) != std::string::npos){
		std::string tmp;
		tmp = url;
		url = url.substr(0, pos);
		std::cout << "pos " << "|" << pos << std::endl;

		url = url.append(tmp.substr(pos + siteName.length()));

		 std::cout << "url kotiki " << "|" << url << "|" << std::endl;

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
		std::cout  << "\x1b[1;92m" << "\n-----SMOTRI REQUEST 70 LINE!!!!!!-------\n" << "\x1b[0m";
		response->makeAnswer(newUrl, 400);
		// std::cout << "Request.cpp, p. 22 - symbol not found" << std::endl;  // переделать
		// exit(-1);
	}
	buffer.erase(0, pos + 2);
}

void Request::makeHeaders() {
		
		std::string tmpStr;
		std::string keyHead;
		std::string valueHead;
		std::size_t delimiter;
		std::size_t pos;

		while (buffer.compare("\r\n")) {
			if ((pos = buffer.find("\r\n")) == std::string::npos) {
				response = new Response();
				std::cout  << "\x1b[1;92m" << "\n-----SMOTRI REQUEST 89 LINE!!!!!!-------\n" << "\x1b[0m";
				response->makeAnswer(newUrl, 400);
				// std::cout << "Request.cpp, p. 67 - symbol not found" << std::endl;  // переделать
				// exit(-1);
				return ;
			}
			// std::cout << "pos " << pos << std::endl;
			tmpStr = buffer.substr(0, pos);
			if ((delimiter = tmpStr.find(": ")) == std::string::npos) {
				response = new Response();
				// --------------------OUT OF RANGE--------------------------
				// terminate called after throwing an instance of 'std::out_of_range'
				// what():  basic_string::substr: __pos (which is 1) > this->size() (which is 0)
				std::cout  << "\x1b[1;92m" << "\n-----SMOTRI REQUEST 98 LINE!!!!!!-------\n" << "\x1b[0m";
				response->makeAnswer(newUrl, 400);
				//exit(-1);
				//return ;
				// --------------------OUT OF RANGE--------------------------
			}
			keyHead = tmpStr.substr(0, delimiter);
			valueHead = tmpStr.substr(delimiter + 2, tmpStr.length() - keyHead.length()-2);
			headers.insert(std::pair<std::string, std::string> (keyHead, valueHead));
			buffer.erase(0, pos+2);
		}
		createCGI();
	}


	void Request::createCGI() {
		std::size_t pos;
		if (url.find("cgi-bin") != std::string::npos) {
			//////////////
			std::cout << "cgi-bin 97 req" << std::endl;  // переделать
			std::string path_info = "PATH_INFO=" + newUrl;
			std::string request_method = "REQUEST_METHOD=";
			request_method.append(method);
			std::string query_string = "QUERY_STRING=";
			query_string.append(url);
			env[3] = strdup("");
			env[4] = strdup("");
			env[5] = strdup("");
			if (method == "POST") {
				std::string content_type = "CONTENT_TYPE="; // Content-Type -key
				std::map<std::string, std::string>::iterator it1 = headers.find("Content-Type");
				if (it1 == headers.end()) {
					response = new Response();
					std::cout  << "\x1b[1;92m" << "\n-----SMOTRI REQUEST 130 LINE!!!!!!-------\n" << "\x1b[0m";
					response->makeAnswer(newUrl, 400);
					return ;
				}
				content_type.append(it1->second);
				std::string content_length = "CONTENT_LENGTH=";
				std::map<std::string, std::string>::iterator it2 = headers.find("Content-Length");
				if (it2 == headers.end()) {
					response = new Response();
					std::cout  << "\x1b[1;92m" << "\n-----SMOTRI REQUEST 139 LINE!!!!!!-------\n" << "\x1b[0m";
					response->makeAnswer(newUrl, 400);
					return ;
				}
				std::cout << "cgi-bin 111 req" << std::endl;
				content_length.append(it2->second); //Content-Length -key
				env[3] = strdup(content_type.c_str());
				env[4] = strdup(content_length.c_str());
			}
			env[0] = strdup(path_info.c_str());
			env[1] = strdup(request_method.c_str());
			env[2] = strdup(query_string.c_str());
			if (cgi->createDynamicHtml(env, newUrl) == -1) {
				response = new Response();
				response->makeAnswer(newUrl, 404);
				return ;
			}
			if ((pos = url.find('.')) != std::string::npos) {
				url = url.substr(0, pos+1) + "html";
				std::cout << "url BIN " << "|" << url << "|" << std::endl;
				cgiRequest = true;
			}
		}
	}

	void Request::makeFullBuffer(){

		std::map<std::string, std::string>::iterator it = headers.find("Content-Length");
		if (it == headers.end()) {
			std::cout  << "\x1b[1;92m" << "\n-----SMOTRI REQUEST 168 LINE!!!!!!-------\n" << "\x1b[0m";
			response->makeAnswer(newUrl, 400); //?????
			// std::cout << "Content Length not found" << std::endl; // убрать
		}
		if (buffer != ""){
			fullBuffer.append(buffer);
			if (fullBuffer.find(endBoundary)!= std::string::npos) {
				std::cout << "Make full buffer AAAAA" << std::endl;
				std::cout << "Max body size " << _maxBodySize << std::endl;
				std::cout << "Full buffer lengtn " << fullBuffer.length() << std::endl;
				if (fullBuffer.length() > _maxBodySize){
					std::cout << "OoOOOOOOOOOOOOOOOOOO" << fullBuffer.length() << std::endl;
					response->makeAnswer(newUrl, 413);
				}
				
				endBody = true;
			}
		}
		// std::cout << "FullBuffer |" << fullBuffer << "|" <<std::endl;
		buffer = "";
	}

	void Request::bodyParsing(){

		std::size_t pos = 0;
		while (fullBuffer.find(endBoundary) != std::string::npos){
			if ((pos = fullBuffer.find("filename=")) != std::string::npos) {
				fullBuffer.erase(0, pos+10);
				filename = fullBuffer.substr(0, fullBuffer.find("\""));
				std::cout << "body parsing filename |" << filename << "|" <<std::endl;
				fullBuffer.erase(0, fullBuffer.find("\r\n\r\n") + 4);
			// } else {
			//     // filename = "cats.gif";
			//     std::cout << "-------NO NAME--------" <<std::endl;
			//     exit(-1);
			}
			std::size_t posEof = fullBuffer.find(boundary);
			std::size_t posN = fullBuffer.rfind("\r\n", posEof);

			std::cout << "----------request file open---------" <<std::endl;
			std::ofstream fout;
			const char *ff = (root + upload + filename).c_str();
			fout.open(ff, std::ofstream::out);
			// fout.open("upload/" + filename, std::ofstream::out);
			// std::size_t posEof = fullBuffer.find(boundary);
			// std::size_t posN = fullBuffer.rfind("\n", posEof);
		   
			// fout << fullBuffer.substr(0, posN-1);
			fout << fullBuffer.substr(0, posN);
			
			fout.close();
			std::cout << "----------request file closed---------" <<std::endl;
			fullBuffer.erase(0, posEof + boundary.length());
		   
			std::cout << "END BODY PARSING" << std::endl;
		}
			fullBuffer = "";
	 }

void Request::requestParsing() {
		if (!parsLine) {
			parsFirstLine();
			parsLine = true;
		}
		if (!parsHeaders) {
			makeHeaders();
			parsHeaders = true;
		}
		//----------------------------findRedirection----------------------------
		if (findRedirection() == 302) {
			response = new Response();
			endBody = true;
			response->makeAnswer(redirect_site, 302);
			return ;
		}
		//----------------------------findRedirection----------------------------
		std::cout << "----------Print map-----------" << std::endl;
		std::map<std::string, std::string>::iterator it = headers.begin();
		for (int i = 0; it != headers.end(); it++, i++) {
			std::cout << "|" << it->first << "|" << it->second << "|"<< std::endl;
		}
		std::cout << "---------End printing--------" << std::endl;
		
		std::cout << "156 request ROOT" << root << "|" << std::endl;
		std::cout << "157 request url " << url << "|" << std::endl;

		response = new Response(url, root);
		if (!method.compare("GET")) {
			// response = new Response(url, root);
			response->checkFile(cgiRequest); // CGI проверить нужен ли он тут вообще
			endBody = true;
			// parsLine = false; // убрать после обработки удаления запросов
			// parsHeaders = f alse; // убрать после обработки удаления запросов
		} else if (!method.compare("POST")) {
			std::map<std::string, std::string>::iterator it = headers.find("Content-Type");
			if (it == headers.end()) {
				std::cout << "ContentType not found" << std::endl; // убрать
			}
			std::string preBoundary;
			preBoundary = it->second.substr(it->second.find("boundary=") + 9);
			boundary = preBoundary.substr(preBoundary.rfind('-') + 1);
			endBoundary = boundary + "--";

			makeFullBuffer();
			if (endBody==true){
				bodyParsing();
				std::cout << "request filename |" << filename << "|" << std::endl; 
				response->checkPostReq(cgiRequest, filename);
			}
			
		} else if (!method.compare("DELETE")){

			// remove((newUrl).c_str());
			// exit(0);       
			response->checkFileDeleting(newUrl);
			endBody = true;
			std::cout << "----------DELETE-----------" << std::endl;

		} else {
			response->makeAnswer(newUrl, 501);
			// std::cout << "UNDEFINED 405 — Method Not Allowed" << std::endl;
		}
}

int Request::findRedirection() {
//     it->getLocationName() /google
// it->getRedirectionSite() http://www.google.ru
// it->getRedirectionSite() http://www.google.ru
// url google
	//std::string slash = "/";
	redirect_code = redirect_name = redirect_site = "";
	for (std::vector<Location>::iterator it = vecLocation.begin(); it != vecLocation.end(); ++it) {
		if (it->getLocationRedirection() == true) {
			std::cout << "-------------getLocationRedirection()-------------" << std::endl;
			redirect_code = it->getLocationIndex();
			redirect_name = it->getLocationName();
			redirect_site = it->getRedirectionSite();
			//std::string r2 = it->getLocationRoot();
			std::cout << "redirection " << redirect_code << std::endl;
			std::cout << "it->getLocationName() " << redirect_name << std::endl;
			std::cout << "it->getRedirectionSite() " << redirect_site << std::endl;
			std::cout << "it->getRedirectionSite() " << redirect_site << std::endl;
			std::cout << "url " << url << std::endl;
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
};

void Request::setLocation(std::vector<Location> &_vecLocation) {
	vecLocation = _vecLocation;
};
