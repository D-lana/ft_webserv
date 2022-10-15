#include "Library.hpp"

Response::Response(){}

Response::Response(std::string& _url, std::string& _root){
	 initMimeType();

	 protocol = "HTTP/1.1";
	 url = _url;
	 answer = "";
	 root = _root;
	 contentSize = 0;
	 _newUrl = root + url;
 }
Response::~Response() {}

std::string Response::makeAnswer(std::string& nn_newUrl, int code) {

	if ((contentType = findContentType()) == "" && code != 302) {
		code = 404;
	}
	const char *newUrl = nn_newUrl.c_str();
	if (code == 100) {
		const char *line;
		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
		line = (nn_newUrl.substr(0, nn_newUrl.length() - 4) + "txt").c_str();  
		std::ifstream stream_head(line, std::ios::in | std::ios::binary);
		std::vector<char> head((std::istreambuf_iterator<char>(stream_head)), std::istreambuf_iterator<char>());

		response << protocol;
		answer = response.str();
		response.write(head.data(), head.size());
		response.write(contents.data(), contents.size());
		answer = response.str();
	   
	} else if (code == 200) {
		
		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		response << protocol << " 200 OK\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
		answer = response.str();
		response.write(contents.data(), contents.size());
		answer = response.str();
	} else if (code == 201){
		contentType = "text/html";

		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
		response << protocol << " 200 OK\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
		answer = response.str();
		response.write(contents.data(), contents.size());
		answer = response.str();

	} else if (code == 404){
		contentType = "text/html";
		nn_newUrl = "errors/404.html";

		newUrl = nn_newUrl.c_str();
		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		response << protocol << " 404 file not found\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
		response.write(contents.data(), contents.size());
		answer = response.str();
		
	} else if (code == 400) {
		contentType = "text/html";
		nn_newUrl = "errors/400.html";
		newUrl = nn_newUrl.c_str();

		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
		response << protocol << " 400 Bad Request\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
		response.write(contents.data(), contents.size());
		answer = response.str();

	} else if (code == 500) {
		contentType = "text/html";
		nn_newUrl = "errors/500.html";
		newUrl = nn_newUrl.c_str();

		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		response << protocol << " 500 Internal Server Error\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
		response.write(contents.data(), contents.size());
		answer = response.str();

	} else if (code == 501) {
		contentType = "text/html";
		nn_newUrl = "errors/501.html";
		newUrl = nn_newUrl.c_str();

		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		response << protocol << " 501 Not Implemented\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
		response.write(contents.data(), contents.size());
		answer = response.str();
	} else if (code == 204) {
		contentType = "text/html";
		nn_newUrl = "errors/204.html";
		newUrl = nn_newUrl.c_str();

		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		response << protocol << " 204 No Content\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
		response.write(contents.data(), contents.size());
		answer = response.str();
	} else if (code == 413) {
		contentType = "text/html";
		nn_newUrl = "errors/413.html";
		newUrl = nn_newUrl.c_str();

		std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
		std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		response << protocol << " 413 Payload Too Large\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
		response.write(contents.data(), contents.size());
		answer = response.str();
	} else if (code == 302) {
		response << "HTTP/1.1 302 Found\r\nLocation: " << nn_newUrl << "\r\n\r\n";
		answer = response.str();
	}
	return(answer);
}

std::string Response::findContentType(){
	size_t posDot = 0;
	std::string key;
	posDot = url.rfind('.');
	
	if (posDot == std::string::npos) {
		return("");
	}
	key = url.substr(++posDot, url.length());
	std::map<std::string, std::string>::iterator it = mimeType.find(key);
	if (it == mimeType.end()) {
		return("");
	}
	return(it->second);
}

void Response::checkFile(bool cgi_request) {
		const char *arr;
		arr = NULL;
		arr = _newUrl.c_str();
		pFile = fopen(arr, "r"); 
		if (pFile!=NULL)
		{
			if (cgi_request) {
				answer = makeAnswer(_newUrl, 100);
			} else {
				answer = makeAnswer(_newUrl, 200);
			}
			fclose (pFile);
		} else {
			answer = makeAnswer(_newUrl, 404);
		}
	}

	void Response::checkPostReq(bool cgi_request, std::string& _filename) {
		filename = _filename;
		const char *fname = ("site_example/upload/" + filename).c_str();
		std::ifstream ifs (fname, std::ios_base::out); 
		if (ifs.is_open()) {
			if (cgi_request) {
				answer = makeAnswer(_newUrl, 100);
			} else {
				answer = makeAnswer(_newUrl, 200);
			}
		}
	}

	std::string& Response::getAnswer(){
		return (answer);
	}

	size_t Response::cutAnswer() {
		if (answer.length() > BUFSIZE) {
			answer = answer.substr(BUFSIZE);
			return(answer.length());
		} 
		return (0);
	}

	size_t Response::getContentSize() {
		return (contentSize);
	}

	void Response::checkFileDeleting(std::string& _newUrl){
		const char *url_tmp = _newUrl.c_str();
		std::ifstream ifs(url_tmp);
		std::cout << _newUrl << std::endl;
		if (ifs.is_open()){
			remove((_newUrl).c_str());
			answer = makeAnswer(_newUrl, 201);
		} else {
			answer = makeAnswer(_newUrl, 204);
		}
	}

void Response::initMimeType() {
	mimeType["txt"]="text/plain; charset=utf-8";
	mimeType["pdf"]="application/pdf";
	mimeType["ico"]="image/x-icon";
	mimeType["cpp"]="text/x-c; charset=utf-8";
	mimeType["jpeg"]="image/jpeg";
	mimeType["png"]="image/png";
	mimeType["gif"]="image/gif";
	mimeType["mp3"]="audio/mpeg";
	mimeType["mp4"]="video/mp4";
	mimeType["html"]="text/html";
	mimeType["ai"]="application/postscript";
	mimeType["aif"]="audio/aiff";
	mimeType["aiff"]="audio/aiff";
	mimeType["ani"]="application/x-navi-animation";
	mimeType["aos"]="application/x-nokia-9000-communicator-add-on-software";
	mimeType["aps"]="application/mime";
	mimeType["arc"]="application/octet-stream";
	mimeType["arj"]="application/arj";
	mimeType["art"]="image/x-jg";
	mimeType["asf"]="video/x-ms-asf";
	mimeType["asm"]="text/x-asm";
	mimeType["asp"]="text/asp; charset=utf-8";
	mimeType["asx"]="application/x-mplayer2";
	mimeType["au"]="audio/basic";
	mimeType["avi"]="video/avi";
	mimeType["bin"]="application/mac-binary";
	mimeType["bm"]="image/bmp";
	mimeType["bmp"]="image/bmp";
	mimeType["boo"]="application/book";
	mimeType["book"]="application/book";
	mimeType["c"]="text/x-c; charset=utf-8";
	mimeType["c++"]="text/plain; charset=utf-8";
	mimeType["ccad"]="application/clariscad";
	mimeType["class"]="application/java";
	mimeType["com"]="application/octet-stream";
	mimeType["conf"]="text/plain; charset=utf-8";
	mimeType["cpt"]="application/mac-compactpro";
	mimeType["css"]="text/css";
	mimeType["dcr"]="application/x-director";
	mimeType["def"]="text/plain; charset=utf-8";
	mimeType["dif"]="video/x-dv";
	mimeType["dir"]="application/x-director";
	mimeType["dl"]="video/dl";
	mimeType["doc"]="application/msword";
	mimeType["dot"]="application/msword";
	mimeType["drw"]="application/drafting";
	mimeType["dvi"]="application/x-dvi";
	mimeType["dwg"]="application/acad";
	mimeType["dxf"]="application/dxf";
	mimeType["dxr"]="application/x-director";
	mimeType["exe"]="application/octet-stream";
	mimeType["gz"]="application/x-compressed";
	mimeType["gzip"]="application/x-gzip";
	mimeType["h"]="text/plain; charset=utf-8";
	mimeType["hlp"]="application/hlp";
	mimeType["htc"]="text/x-component";
	mimeType["htm"]="htm";
	mimeType["htmls"]="text/html";
	mimeType["htt"]="text/webviewhtml";
	mimeType["ice"]="x-conference/x-cooltalk";
	mimeType["inf"]="application/inf";
	mimeType["jam"]="audio/x-jam";
	mimeType["jav"]="text/plain; charset=utf-8";
	mimeType["java"]="text/plain; charset=utf-8";
	mimeType["jcm"]="application/x-java-commerce";
	mimeType["jfif"]="image/jpeg";
	mimeType["jfif-tbnl"]="image/jpeg";
	mimeType["jpe"]="image/jpeg";
	mimeType["jpg"]="image/jpeg";
	mimeType["jps"]="image/x-jps";
	mimeType["js"]="application/x-javascript";
	mimeType["latex"]="application/x-latex";
	mimeType["lha"]="application/lha";
	mimeType["lhx"]="application/octet-stream";
	mimeType["list"]="text/plain; charset=utf-8";
	mimeType["lsp"]="application/x-lisp";
	mimeType["lst"]="text/plain; charset=utf-8";
	mimeType["lzh"]="application/octet-stream";
	mimeType["lzx"]="application/lzx";
	mimeType["m3u"]="audio/x-mpequrl";
	mimeType["man"]="application/x-troff-man";
	mimeType["mid"]="application/x-midi";
	mimeType["midi"]="application/x-midi";
	mimeType["mod"]="audio/mod";
	mimeType["mov"]="video/quicktime";
	mimeType["movie"]="video/x-sgi-movie";
	mimeType["mp2"]="audio/mpeg";
	mimeType["mpa"]="audio/mpeg";
	mimeType["mpg"]="audio/mpeg";
	mimeType["mpga"]="audio/mpeg";
	mimeType["pas"]="text/pascal";
	mimeType["pcl"]="application/vnd.hp-pcl";
	mimeType["pct"]="image/x-pict";
	mimeType["pcx"]="image/x-pcx";
	mimeType["pic"]="image/pict";
	mimeType["pict"]="image/pict";
	mimeType["pl"]="text/plain";
	mimeType["pm"]="image/x-xpixmap";
	mimeType["pm4"]="application/x-pagemaker";
	mimeType["pm5"]="application/x-pagemaker";
	mimeType["pot"]="application/mspowerpoint";
	mimeType["ppa"]="application/vnd.ms-powerpoint";
	mimeType["pps"]="application/mspowerpoint";
	mimeType["ppt"]="application/mspowerpoint";
	mimeType["ppz"]="application/mspowerpoint";
	mimeType["ps"]="application/postscript";
	mimeType["psd"]="application/octet-stream";
	mimeType["pwz"]="application/vnd.ms-powerpoint";
	mimeType["py"]="text/x-script.phyton";
	mimeType["pyc"]="applicaiton/x-bytecode.python";
	mimeType["qt"]="video/quicktime";
	mimeType["qtif"]="image/x-quicktime";
	mimeType["ra"]="audio/x-pn-realaudio";
	mimeType["ram"]="audio/x-pn-realaudio";
	mimeType["rm"]="application/vnd.rn-realmedia";
	mimeType["rpm"]="audio/x-pn-realaudio-plugin";
	mimeType["rtf"]="application/rtf";
	mimeType["rtx"]="application/rtf";
	mimeType["rv"]="video/vnd.rn-realvideo";
	mimeType["sgml"]="text/sgml";
	mimeType["sh"]="application/x-bsh";
	mimeType["shtml"]="text/html";
	mimeType["ssi"]="text/x-server-parsed-html";
	mimeType["tar"]="application/x-tar";
	mimeType["tcl"]="application/x-tcl";
	mimeType["text"]="text/plain; charset=utf-8";
	mimeType["tgz"]="application/gnutar";
	mimeType["tif"]="image/tiff";
	mimeType["tiff"]="image/tiff";
	mimeType["uri"]="text/uri-list";
	mimeType["vcd"]="application/x-cdlink";
	mimeType["vmd"]="application/vocaltec-media-desc";
	mimeType["vrml"]="application/x-vrml";
	mimeType["vsd"]="application/x-visio";
	mimeType["vst"]="application/x-visio";
	mimeType["vsw"]="application/x-visio";
	mimeType["wav"]="audio/wav";
	mimeType["wmf"]="windows/metafile";
	mimeType["xla"]="application/excel";
	mimeType["xlb"]="application/excel";
	mimeType["xlc"]="application/excel";
	mimeType["xld"]="application/excel";
	mimeType["xlk"]="application/excel";
	mimeType["xll"]="application/excel";
	mimeType["xlm"]="application/excel";
	mimeType["xls"]="application/excel";
	mimeType["xlt"]="application/excel";
	mimeType["xlv"]="application/excel";
	mimeType["xlw"]="application/excel";
	mimeType["xm"]="audio/xm";
	mimeType["xml"]="xml";
	mimeType["z"]="application/x-compress";
	mimeType["zip"]="application/x-compressed";
}
