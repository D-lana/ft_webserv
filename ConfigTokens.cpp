/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigTokens.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:40:24 by marvin            #+#    #+#             */
/*   Updated: 2022/09/17 16:40:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

ConfigTokens::ConfigTokens() {

	std::string servWords[] = { "listen", "server_name", "autoindex", "root", "index", "methods", "client_max_body_size", "error_page", "upload_path" };

	for (size_t i = 0; i < 9; ++i) {
		serverData.push_back(servWords[i]);
	}

	std::string locationWords[] = { "location", "methods", "root", "redirection", "error_page", "bin_path_py", "index", "upload_path", "autoindex" };

	for (size_t i = 0; i < 9; ++i) {
		locationData.push_back(locationWords[i]);
	}

	std::string allWords[] = { "listen", "server", "server_name", "location", "autoindex", "root", "index", "methods", "client_max_body_size", "error_page", "redirection", "bin_path_py", "upload_path", ";", "{", "}" };

	for (size_t i = 0; i < 16; ++i) {
		serverTokens[allWords[i]];
	}
}

ConfigTokens::ConfigTokens(int key) {
	std::cout << "self-constructor \n";
	std::string errorConstructor[] = {
		"<html>",
		"<head>",
		"<title>KEY</title>",
		"</head>",
		"<body>",
		"<center>",
		"<br></br>",
		"<h1 style=\"font-size:40px;\" >Error KEY</h1>",
		"<h2 style=\"font-size:20px;\" >VALUE</h2>",
		"</center>",
		"</body>",
		"</html>" };

	for (size_t i = 0; i < 12; ++i) {
		errorPage.push_back(errorConstructor[i]);
	}

    errorMap["400"] = "BadRequest";
    // errorMap["403"] = "Forbidden";
    errorMap["404"] = "NotFound";
    // errorMap["405"] = "MethodNotAllowed";
    // errorMap["406"] = "NotAcceptable";
    // errorMap["413"] = "ContentTooLarge";
    // errorMap["415"] = "UnsupportedMediaType";
    // errorMap["500"] = "InternalServerError";
    // errorMap["505"] = "BadRequest";
    // errorMap["409"] = "Conflipwct";
}

ConfigTokens::~ConfigTokens() { }