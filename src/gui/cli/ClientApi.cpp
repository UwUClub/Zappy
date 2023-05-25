#include "ClientApi.hpp"
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <functional>
#include <unordered_map>

namespace Zappy::GUI {
    ClientApi::ClientApi(const std::string &aAddress, unsigned int aPort, const std::string &aTeamName)
        : _address(const_cast<char *>(aAddress.c_str())), _port(aPort), _teamName(aTeamName), _connectStatus(-1),
          _readBuffer(""), _writeBuffer(""), _serverFd(-1)
    {}

    ClientApi::~ClientApi()
    {
        if (_serverFd != -1) {
            close(_serverFd);
        }
    }

    void ClientApi::joinGame()
    {
        _serverFd = socket(PF_INET, SOCK_STREAM, 0);
        struct sockaddr_in myAddr = getSockaddr(inet_addr(_address), _port);
        _connectStatus =
            connect(_serverFd, reinterpret_cast<const struct sockaddr *>(&myAddr), sizeof(struct sockaddr_in));
        if (_connectStatus == -1) {
            throw ClientException(strerror(errno));
        }
    }

    int ClientApi::update()
    {
        fd_set myReadFds;
        fd_set myWriteFds;

        FD_ZERO(&myReadFds);
        FD_ZERO(&myWriteFds);
        FD_SET(_serverFd, &myReadFds);
        if (_writeBuffer.length() > 0) {
            FD_SET(_serverFd, &myWriteFds);
        }
        select(FD_SETSIZE, &myReadFds, &myWriteFds, nullptr, nullptr);
        if (FD_ISSET(_serverFd, &myReadFds)) {
            readFromServer();
        }
        if (FD_ISSET(_serverFd, &myWriteFds)) {
            writeToServer();
        }
        return 0;
    }

    void ClientApi::sendCommand(const std::string &aCommand)
    {
        _writeBuffer += aCommand + "\n";
    }

    int ClientApi::getConnectStatus() const
    {
        return _connectStatus;
    }

    int ClientApi::getServerFd() const
    {
        return _serverFd;
    }

    struct sockaddr_in ClientApi::getSockaddr(in_addr_t aAddress, unsigned int aPort)
    {
        struct sockaddr_in myAddr;

        myAddr.sin_family = AF_INET;
        myAddr.sin_port = htons(static_cast<short unsigned int>(aPort));
        myAddr.sin_addr.s_addr = aAddress;
        memset(&(myAddr.sin_zero), '\0', 8);
        return myAddr;
    }

    void ClientApi::readFromServer()
    {
        char myStr[4096];
        int const myReadSize = static_cast<int>(read(_serverFd, myStr, 4096));

        if (myReadSize == -1) {
            throw ClientException(strerror(errno));
        }
        if (myReadSize == 0) {
            throw ClientException("Server disconnected");
        }
        myStr[myReadSize] = '\0';
        _readBuffer += myStr;
        std::cout << "@read: " << _readBuffer;
        ParseServerResponses();
    }

    void ClientApi::writeToServer()
    {
        dprintf(_serverFd, "%s", _writeBuffer.c_str());
        std::cout << "@write: " << _writeBuffer;
        _writeBuffer = "";
    }

    void ClientApi::ParseServerResponses()
    {
        std::unordered_map<std::string, std::function<void(ClientApi &, std::string)>> myResponses = {
            { "WELCOME", &ClientApi::ReceiveWelcome },
            { "msz", &ClientApi::ReceiveMsz },
        };

        while (_readBuffer.find("\n") != std::string::npos) {
            std::string myResponse = _readBuffer.substr(0, _readBuffer.find("\n"));
            std::string myCommand = myResponse.substr(0, myResponse.find(" "));
            std::string myArgs = myResponse.substr(myResponse.find(" ") + 1);

            if (myResponses.find(myCommand) != myResponses.end()) {
                myResponses[myCommand](*this, myArgs);
            }
            _readBuffer = _readBuffer.substr(_readBuffer.find("\n") + 1);
        }
    }

    void ClientApi::ReceiveWelcome(__attribute__((unused)) std::string aResponse)
    {
        _writeBuffer += _teamName + "\n";
    }

    void ClientApi::ReceiveMsz(std::string aResponse)
    {
        std::string myX = aResponse.substr(0, aResponse.find(" "));
        std::string myY = aResponse.substr(aResponse.find(" ") + 1);

        _serverData._mapSize = std::make_pair(std::stoi(myX), std::stoi(myY));
    }
} // namespace Zappy::GUI
