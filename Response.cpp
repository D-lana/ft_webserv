#include "Library.hpp"

Response::Response(){}

Response::Response(std::string& _url, std::string& _root){
    //  fileFound = false;
     initMimeType();

     protocol = "HTTP/1.1";
     url = _url;
    //  streamPos = 0;  //part answer
     answer = "";
     root = _root;
     contentSize = 0;
     _newUrl = root + url; // new

    std::cout << "14 response root" << "|" << root << "|" << std::endl;
    std::cout << "14 response newUrl" << "|" << _newUrl << "|" << std::endl;
    //  std::cout << "url response " << url << std::endl;

 }
Response::~Response() {

}

    std::string Response::makeAnswer(std::string& nn_newUrl, int code) {

     if ((contentType = findContentType()) == ""){
         code = 404;
     }
    std::cout << "\x1b[1;92m" << "> MakeAnswer 26 Response " << code << "\n" << "\x1b[0m";
    const char *newUrl = nn_newUrl.c_str();
    if (code == 100) {
        std::cout << "BBBBBB" << std::endl;
        // std::string line;
        const char *line;
        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        
        line = (nn_newUrl.substr(0, nn_newUrl.length() - 4) + "txt").c_str();
        std::cout << "\x1b[1;92m" << "> line: " << line  << "\n" << "\x1b[0m";
  
        std::ifstream stream_head(line, std::ios::in | std::ios::binary);
        std::vector<char> head((std::istreambuf_iterator<char>(stream_head)), std::istreambuf_iterator<char>());

        response << protocol; //<< //" 200 OK\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        answer = response.str();
        response.write(head.data(), head.size());
        response.write(contents.data(), contents.size());
        std::cout << "---------Content size---------" << contents.size() << std::endl;
        answer = response.str();
       
        std::cout << "\x1b[1;92m" << "> answer: " << answer  << "\n" << "\x1b[0m";
       

    } else if (code == 200) {
        std::cout << "AAAAAAAAAAA" << std::endl;
        // contentType = findContentType();

        // std::cout << "newUrl resp 52 |" << newUrl << "|" << std::endl;
        // std::cout << "\x1b[1;95m" << "\b\b>>>>> RESPONSE <<<<<\n" << "\x1b[0m"; 
  
        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

        // contentSize = contents.size(); // временно

        response << protocol << " 200 OK\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        answer = response.str();
        response.write(contents.data(), contents.size());
        std::cout << "---------Content size---------" << contents.size() << std::endl;
        answer = response.str();

        std::cout << "\x1b[1;95m" << "\b\b>>>>> RESPONSE END <<<<<\n" << "\x1b[0m"; 
    } else if (code == 201){
        
        contentType = "text/html";
        // newUrl = "site_example/deleted.html";

        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        response << protocol << " 200 OK\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        // response << protocol << " 302 \r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\nLocation: http://localhost:8080/site_example/deleted.html" << "\r\n\r\n";
        answer = response.str();
        // std::cout << "contents.data()" << contents.data() << std::endl;
        response.write(contents.data(), contents.size());
        answer = response.str();
        std::cout << "\x1b[1;92m" << ">  MakeAnswer 84 code=201 if " << code << "\n" << "\x1b[0m";

        // exit(-1);

    } else if (code == 404){
        std::cout << "\x1b[1;92m" << "> makeAnswer 93 err 404 " << code << "\n" << "\x1b[0m";
        contentType = "text/html";
        nn_newUrl = "errors/404.html";
        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

        response << protocol << " 404 file not found\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        response.write(contents.data(), contents.size());
        answer = response.str();
        
    } else if (code == 400) {
        std::cout << "\x1b[1;92m" << "> response 111 makeAnswer err 400 " << code << "\n" << "\x1b[0m";
        contentType = "text/html";
        nn_newUrl = "errors/400.html";

        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        std::cout << "\x1b[1;93m" << "> response 117\n" << "\x1b[0m";

        response << protocol << " 400 Bad Request\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        response.write(contents.data(), contents.size());
        std::cout << "\x1b[1;93m" << "> response 121\n" << "\x1b[0m";

        answer = response.str();
        std::cout << "\x1b[1;93m" << "> response 124\n" << "\x1b[0m";

    } else if (code == 500) {
        contentType = "text/html";
        nn_newUrl = "errors/500.html";

        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

        response << protocol << " 500 Internal Server Error\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        response.write(contents.data(), contents.size());
        answer = response.str();

    } else if (code == 501) {
        contentType = "text/html";
        nn_newUrl = "errors/501.html";

        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

        response << protocol << " 501 Not Implemented\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        response.write(contents.data(), contents.size());
        answer = response.str();

    } else if (code == 204) {
        contentType = "text/html";
        nn_newUrl = "errors/204.html";

        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

        response << protocol << " 204 No Content\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        response.write(contents.data(), contents.size());
        answer = response.str();
    } else if (code == 413) {
        contentType = "text/html";
        nn_newUrl = "errors/413.html";

        std::ifstream stream(newUrl, std::ios::in | std::ios::binary);
        std::vector<char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

        response << protocol << " 413 Payload Too Large\r\nContent-Type: " << contentType << "\r\nContent-Length: " << contents.size() << "\r\n\r\n";
        response.write(contents.data(), contents.size());
        answer = response.str();
    } else if (code == 302) {
        //HTTP/1.1 302 Found
        //Location: http://www.example.org/index.asp
        response << "HTTP/1.1 302 Found\r\nLocation: " << nn_newUrl << "\r\n\r\n";
        answer = response.str();
    }
    std::cout << "\x1b[1;93m" << "> return(answer); response 174\n" << "\x1b[0m";
    return(answer);
}

std::string Response::findContentType(){
    size_t posDot = 0;
    
    std::string key;
    std::cout << "url response p 97 |" << url << "|" << std::endl;
    posDot = url.rfind('.');
    //-------------------ЧТО-ТО НЕ ТАК ПРОИСХОДИТ (/kotiki/)-----------------------------
    if (posDot == std::string::npos) {
        
        std::cout << "Response.cpp, p. 79 - Dot not found" << std::endl;  // переделать
        return("");
        // exit(-1);
    }
    key = url.substr(++posDot, url.length());
    std::map<std::string, std::string>::iterator it = mimeType.find(key);
    if (it == mimeType.end()) {
        std::cout << "ContentType not found" << std::endl; // убрать
        return("");
    }

    // std::cout << "key = " << key << std::endl;
    // std::cout << "value = " << it->second << std::endl;

    return(it->second);
}

void Response::checkFile(bool cgi_request) {
        char arr[_newUrl.length() + 1];
        memset (arr, 0, (_newUrl.length() + 1));
        strcpy(arr, _newUrl.c_str());
        //  std::cout << "NEWURLLLL processor " << newUrl << "\n";
        //  std::cout << "ARR processor " << arr << "\n"; 
        pFile = fopen(arr, "r");
        std::cout << "----cgi_request----> " << cgi_request << arr << "\n"; 
        // if (cgi_request == true) {
        //     answer = makeAnswer(newUrl, 100);
        //     //fclose (pFile);
        // }  
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
        std::cout << "-----Check Post Request-------" << std::endl;
        std::ifstream ifs (fname); 
        std::cout << "-----filename-------|" << filename << "|" << std::endl;
        if (ifs.is_open()){
            std::cout << "-----Check Well Post Request-------" << std::endl;
            if (cgi_request) {
                answer = makeAnswer(_newUrl, 100);
            } else {
                // std::cout  << "\x1b[1;92m" << "\n-----SMOTRI RESPONSE 236 LINE!!!!!!-------\n" << "\x1b[0m";
                answer = makeAnswer(_newUrl, 200); // -----------------------------
            }
        } else {
            std::cout << "-----Check Wrong Post Request-------" << std::endl;
            answer = makeAnswer(_newUrl, 500);
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

    // void Response::setAnswer(std::string _answer){
    //     answer = _answer;
    // }
    void Response::checkFileDeleting(std::string& _newUrl){
        // std::string tmp = "site_example/deleted.html";
        const char *url = _newUrl.c_str();
        std::ifstream ifs(url);
        std::cout << _newUrl << std::endl;
        // ifs.open(_newUrl);
        if (ifs.is_open()){
            remove((_newUrl).c_str());
            // ifs.close();
            // std::cout << "AAAAAAA" << std::endl;
            // _newUrl = "site_example/deleted.html";
            answer = makeAnswer(_newUrl, 201);
            //  std::cout << "_newUrl resp 204 |" << _newUrl << "|" << std::endl;
        //    exit(0);
        } else {
            answer = makeAnswer(_newUrl, 204);
            // ifs.close();
           // std::cout << "File wasn't deleted" << std::endl;
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

// void Response::initCodeStatus() {
//     codeStatus["403"] = "Forbidden";
//     codeStatus["404"] = "Not Found";
// }