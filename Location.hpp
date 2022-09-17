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

        class Location {
        
        private:

            std::string _locationName;
            bool _locationAutoIndex;
            std::string _locationRoot;
            std::string _locationIndex;
            std::string _locationUploadPath;
            bool        _locationRedirection;
            std::string _locationBinPath;
            std::string _locationPathCgi;
            int         _locationErrorCode;
            std::string _locationErrorDescription;
            std::string _locationMethod;
            bool        _cgiInLocation;

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
            void setIsCgi(const bool& cgi);
            void setLocationPathCgi(const std::string&);
            void setLocationError(const int &code, const std::string &description);
            void setLocationMethod(const std::string& str);

            const std::string& getLocationPathCgi(void);
            const bool& getCgiInLocation(void);
            const bool& getLocationRedirection(void);

};


#endif