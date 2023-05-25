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

namespace Zappy::GUI {
    ClientApi::ClientApi(const std::string& aAddress, unsigned int aPort, const std::string& aTeamName)
        : _address(const_cast<char *>(aAddress.c_str())), _port(aPort), _teamName(aTeamName), _connectStatus(-1),
          _readBuffer(strdup("")), _writeBuffer(strdup("")), _serverFd(-1)
    {}

    ClientApi::~ClientApi()
    {
        if (_readBuffer != nullptr) {
            free(_readBuffer);
        }
        if (_writeBuffer != nullptr) {
            free(_writeBuffer);
        }
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
        _writeBuffer = concatStr(_writeBuffer, (_teamName + "\n").c_str());
        update();
    }

    int ClientApi::update()
    {
        fd_set myReadFds;
        fd_set myWriteFds;

        FD_ZERO(&myReadFds);
        FD_ZERO(&myWriteFds);
        FD_SET(_serverFd, &myReadFds);
        if ((_writeBuffer != nullptr) && strlen(_writeBuffer) > 0) {
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
        _readBuffer = concatStr(_readBuffer, myStr);
        std::cout << "@read: " << _readBuffer;
    }

    void ClientApi::writeToServer()
    {
        dprintf(_serverFd, "%s", _writeBuffer);
        std::cout << "@write: " << _writeBuffer;
        free(_writeBuffer);
        _writeBuffer = strdup("");
    }

    char *ClientApi::concatStr(char *aStr1, const char *aStr2)
    {
        char *myResult = static_cast<char *>(malloc(strlen(aStr1) + strlen(aStr2) + 1));

        strcpy(myResult, aStr1);
        strcat(myResult, aStr2);
        free(aStr1);
        return myResult;
    }
} // namespace Zappy::GUI
