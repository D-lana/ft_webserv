/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:39:02 by marvin            #+#    #+#             */
/*   Updated: 2022/09/08 21:39:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location() {
	_locationName.clear();
    _locationAutoIndex = 0;;
    _locationRoot.clear();
    _locationIndex.clear();
    _locationUploadPath.clear();
    _locationRedirection = 0;
    _locationBinPath.clear();
    _locationPathCgi.clear();
    _locationErrorCode = 0;
    _locationErrorDescription.clear();
    _locationMethod.clear();
    _cgiInLocation = 0;
	};

Location::~Location() {
	};

void Location::setLocationName(const std::string& str) {
	_locationName = str;
};

void Location::setLocationAutoIndex(const bool& index) {
_locationAutoIndex = index;
};

void Location::setLocationRoot(const std::string& str) {
_locationRoot = str;
};

void Location::setLocationIndex(const std::string& str) {
_locationIndex = str;
};

void Location::setLocationUploadPath(const std::string& str) {
	_locationUploadPath = str;
};

void Location::setLocationRedirection(const bool& redirection) {
	_locationRedirection = redirection;
}

void Location::setLocationBinPath(const std::string& str) {
	_locationBinPath = str;
};

void Location::setIsCgi(const bool& cgi) {
	_cgiInLocation = cgi;
};

void Location::setLocationPathCgi(const std::string& cgi) {
	_locationPathCgi = cgi;
};

void Location::setLocationError(const int &code, 
		const std::string &description) {
	_locationErrorDescription = description;
	_locationErrorCode = code;
};
void Location::setLocationMethod(const std::string& str) {
	_locationMethod = str;
};

const bool& Location::getLocationRedirection(void) {
	return _locationRedirection;	
};

const std::string& Location::getLocationName(void) {
	return _locationName;
};

const std::string& Location::getLocationIndex() {
	return _locationIndex;
};

const std::string& Location::getLocationRoot() {
	return _locationRoot;
};

const std::string& Location::getLocationUpload() {
	return _locationUploadPath;
};

const std::string& Location::getLocationPathCgi(void) {
	return _locationPathCgi;
};

const bool& Location::getCgiInLocation(void) {
	return _cgiInLocation;
};

const std::string& Location::getLocationBinPath(void) {
	return _locationBinPath;
};