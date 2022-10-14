#include "Library.hpp"

ConfigTokens::ConfigTokens() {

	std::string servWords[] = { "listen", "server_name", "autoindex", "root", 
	"index", "methods", "client_max_body_size", "error_page", "upload_path" };

	for (size_t i = 0; i < 9; ++i) {
		serverData.push_back(servWords[i]);
	}

	std::string locationWords[] = { "location", "methods", "root", "redirection", 
	"error_page", "bin_path_py", "bin_path_sh", "path_cgi", "index", "upload_path", 
	"autoindex" };

	for (size_t i = 0; i < 11; ++i) {
		locationData.push_back(locationWords[i]);
	}

	std::string allWords[] = { "listen", "server", "server_name", "location", 
	"autoindex", "root", "index", "methods", "client_max_body_size", 
	"error_page", "redirection", "bin_path_py", "bin_path_sh", "path_cgi",
	"upload_path", ";", "{", "}" };

	for (size_t i = 0; i < 18; ++i) {
		serverTokens[allWords[i]];
	}
}

ConfigTokens::~ConfigTokens() { }