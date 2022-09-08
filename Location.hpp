/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:32:30 by marvin            #+#    #+#             */
/*   Updated: 2022/08/30 11:32:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <vector>
#include <iostream>
// #include <map>
// #include <types.h>

// class Location : public ALocation {
// class Location {

//     private:

//         std::string _url;
// 		// std::string _binPathPy;
//         // std::string _binPathSh;
// //		std::string _uploadPath;
//         bool _folder;
//         bool _redirect;
//         bool _cgi;
//         int _returnCode;
//         std::map<int, std::string> _error;

        class Location {
        
        private:

            std::string _locationName;
            bool _locationAutoIndex;
            std::string _locationRoot;
            std::string _locationIndex;
            std::string _locationUploadPath;
            bool        _locationRedirection;
            std::string _locationBinPath;
            bool        _locationPathCgi;
            int         _locationErrorCode;
            std::string _locationErrorDescription;
            std::string _locationMethod;

    public:
            Location();
            virtual ~Location();

            void setLocationName(const std::string& str);
            void setLocationAutoIndex(const bool& index);
            void setLocationRoot(const std::string& str);
            void setLocationIndex(const std::string& str);
            void setLocationUploadPath(const std::string& str);
            void setLocationRedirection(const bool& redirection);
            // void setLocationRedirectionCode(const bool& code);
            void setLocationBinPath(const std::string& str);
            void setLocationPathCgi(const bool& cgi);
            void setLocationError(const int &code, const std::string &description);
            void setLocationMethod(const std::string& str);

            const bool& getLocationPathCgi(void);
        };





	// public:

    //     FtLocation();
    //     // FtLocation &operator=(const FtLocation &other);
    //     virtual ~FtLocation();

	// 	void setUrl(const std::string &url);
    //     const std::string &getUrl() const;

		// void setBinPathPy(const std::string &path);
		// const std::string &getBinPathPy() const;

        // void setBinPathSh(const std::string &path);
        // const std::string &getBinPathSh() const;

//		void setUploadPath(const std::string &path);
//		const std::string &getUploadPath() const;

//         void setFolder(const bool &status);
//         const bool &getCheckFolder() const;

//         void seRedirect(const bool &status);
//         const bool &getCheckRedirect() const;

//         void setCgi(const bool &status);
//         const bool &getCheckCgi() const;

//         void setReturnCode(const int &redirectionCode);
//         const int &getReturnCode() const;

// };

#endif