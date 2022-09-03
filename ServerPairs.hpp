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
// #include "Parser.hpp"

class ServerPairs {

    private:

        // u_short _ftPort;
        // in_addr_t _ftHost;
        std::string _ftServName;
        int _maxBodySize;
        bool _autoIndex;

    public:

        ServerPairs();
        ServerPairs &operator=(const ServerPairs &other);
        virtual ~ServerPairs();

        // void setFtPort(const int &port);
        // const u_short &getFtPort() const;

        // void setFtHost(const std::string &host);
        // const in_addr_t &getFtHost() const;

        // void setServName(const std::string &serverName);
        // const std::string &getServName() const;

        // void setMaxBodySize(const int &maxBodySize);
        // const int &getMaxBodySize() const;

//        void setAutoIndex(const bool &autoIndex);
//        const bool &getAutoIndex() const;

        // std::vector<FtLocation> &getFtLocations();

    };

#endif