#ifndef SERVERPAIRS_HPP
#define SERVERPAIRS_HPP

# include "Library.hpp"

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
        std::vector<Location> _locations;


    public:

        ServerPairs();
        ServerPairs &operator=(const ServerPairs &other);
        virtual ~ServerPairs();

        void setPort(const int &port);

        void setHost(const std::string &host);

        void setServName(const std::string &serverName);
       void setAutoIndex(const bool &autoIndex);

       void setRoot(const std::string &root);

        void setIndex(const std::string &index);

        void setUpload(const std::string &path);

        void setMaxBodySize(const int &maxBodySize);

        void setError(const int &code, const std::string &description);
        void setMethod(const std::string &method);

        std::vector<Location>& getLocations();
        const u_short& getPort() const;
        const std::string& getRoot() const; 
        const std::string& getIndex();
        const std::string& getServName();
        const in_addr_t& getHost() const;
        const std::string& getUpload();
        const int& getBodySize();

    };

#endif