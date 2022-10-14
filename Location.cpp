# include "Library.hpp"

Location::Location() {
	_locationName.clear();
    _locationAutoIndex = 0;;
    _locationRoot.clear();
    _locationIndex.clear();
    _locationUploadPath.clear();
    _locationRedirection = 0;
	_redirectionSite.clear();
    _locationBinPathPy.clear();
	_locationBinPathSh.clear();
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

void Location::setRedirectionSite(const std::string& str) {
	_redirectionSite = str;
}

void Location::setLocationBinPathPy(const std::string& str) {
	_locationBinPathPy = str;
};

void Location::setLocationBinPathSh(const std::string& str) {
	_locationBinPathSh = str;
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

const std::string& Location::getLocationBinPathPy(void) {
	return _locationBinPathPy;
};

const std::string& Location::getLocationBinPathSh(void) {
	return _locationBinPathSh;
};

const std::string& Location::getRedirectionSite(void) {
	return _redirectionSite;
};