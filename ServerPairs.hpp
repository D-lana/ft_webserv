/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerPairs.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:19:29 by marvin            #+#    #+#             */
/*   Updated: 2022/08/30 11:19:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERPAIRS_HPP
#define SERVERPAIRS_HPP

#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
// #include "Parser.hpp"
 #include "Location.hpp"

// struct ConfigData { // struct ValidConfigKeys
// 		std::vector<std::string>			serverData;
// 		std::vector<std::string>			locationData;
// 		std::map<std::string, int>			serverTokens;
// 		std::map<std::string, std::string>	errorsMap;
// 		std::vector<std::string>			errorPage;
// 		std::vector<std::string>			autoindexPage;
// 	};

class ServerPairs {

    private:

        u_short _port;
        in_addr_t _host;
        std::string _servName;
        bool _autoIndex;
        std::string _root;
        std::string _index;
        std::string _uploadPath;
        int _maxBodySize;
        int _errorCode;
        std::string _errorDescription;
        std::string _method;
        // ConfigData* tokens;
        std::vector<Location> _locations;


    public:

        ServerPairs();
        ServerPairs &operator=(const ServerPairs &other);
        virtual ~ServerPairs();

        void setPort(const int &port);
        const u_short &getPort() const;

        void setHost(const std::string &host);
        const in_addr_t &getHost() const;

        void setServName(const std::string &serverName);
        // const std::string &getServName() const;

       void setAutoIndex(const bool &autoIndex);
//        const bool &getAutoIndex() const;

       void setRoot(const std::string &root);

        void setIndex(const std::string &index);

        void setUpload(const std::string &path);

        void setMaxBodySize(const int &maxBodySize);
        // const int &getMaxBodySize() const;

        void setError(const int &code, const std::string &description);
        void setMethod(const std::string &method);

        std::vector<Location> &getLocations();

    };

#endif