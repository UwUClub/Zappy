#include "ClientApi.hpp"
#include <arpa/inet.h>
#include <errno.h>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_map>
#include <utility>

namespace Zappy::GUI {
    ClientApi::ClientApi(std::string aAddress, unsigned int aPort, std::string aTeamName)
        : _address(std::move(aAddress)), _port(aPort), _teamName(std::move(aTeamName)), _connectStatus(-1), _serverFd(-1)
    {}

    ClientApi::~ClientApi()
    {
        if (_serverFd != -1) {
            close(_serverFd);
        }
    }

    void ClientApi::joinGame()
    {
        struct sockaddr_in myAddr = getSockaddr(inet_addr(_address.c_str()), _port);

        _serverFd = socket(PF_INET, SOCK_STREAM, 0);
        _connectStatus =
            connect(_serverFd, reinterpret_cast<const struct sockaddr *>(&myAddr), sizeof(struct sockaddr_in));
        if (_connectStatus == -1) {
            throw ClientException(strerror(errno));
        }
    }

    int ClientApi::update()
    {
        fd_set myReadFds = {0};
        fd_set myWriteFds = {0};

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
        const constexpr int bufferSize = 8;
        struct sockaddr_in myAddr = {};

        myAddr.sin_family = AF_INET;
        myAddr.sin_port = htons(static_cast<short unsigned int>(aPort));
        myAddr.sin_addr.s_addr = aAddress;
        memset(&(myAddr.sin_zero), '\0', bufferSize);
        return myAddr;
    }

    void ClientApi::readFromServer()
    {
        char myStr[4096] = {0};
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
        static std::unordered_map<std::string, std::function<void(ClientApi &, std::string)>> myResponses = {
            {"WELCOME", &ClientApi::ReceiveWelcome},
            {"msz", &ClientApi::ReceiveMsz},
            {"bct", &ClientApi::ReceiveBct},
            {"mct", &ClientApi::ReceiveMct}
        };

        while (_readBuffer.find('\n') != std::string::npos) {
            std::string const myResponse = _readBuffer.substr(0, _readBuffer.find('\n'));
            std::string const myCommand = myResponse.substr(0, myResponse.find(' '));
            std::string const myArgs = myResponse.substr(myResponse.find(' ') + 1);

            if (myResponses.find(myCommand) != myResponses.end()) {
                myResponses[myCommand](*this, myArgs);
            }
            _readBuffer = _readBuffer.substr(_readBuffer.find('\n') + 1);
        }
    }

    void ClientApi::ReceiveWelcome(__attribute__((unused)) const std::string& aResponse)
    {
        _writeBuffer += _teamName + "\n";
    }

    void ClientApi::ReceiveMsz(const std::string& aResponse)
    {
        std::string const myX = aResponse.substr(0, aResponse.find(' '));
        std::string const myY = aResponse.substr(aResponse.find(' ') + 1);

        _serverData._mapSize = std::make_pair(std::stoi(myX), std::stoi(myY));
    }

    void ClientApi::ReceiveBct(const std::string& aResponse)
    {
        std::vector<int> myResources;
        std::string myArg = aResponse;

        while (myArg.find(' ') != std::string::npos) {
            std::string const myResource = myArg.substr(0, myArg.find(' '));

            myResources.push_back(std::stoi(myResource));
            myArg = myArg.substr(myArg.find(' ') + 1);
        }
        myResources.push_back(std::stoi(myArg));

        if (std::find(_serverData._mapTiles.begin(), _serverData._mapTiles.end(), myResources) == _serverData._mapTiles.end()) {
            _serverData._mapTiles.push_back(myResources);
        } else {
            _serverData._mapTiles.erase(std::find(_serverData._mapTiles.begin(), _serverData._mapTiles.end(), myResources));
            _serverData._mapTiles.push_back(myResources);
        }
    }

    void ClientApi::ReceiveMct(const std::string& aResponse)
    {
        std::pair<int, int> const myMapSize = _serverData._mapSize;
        std::vector<int> const myResources;

        for (int myY = 0; myY < myMapSize.second; myY++) {
            for (int myX = 0; myX < myMapSize.first; myX++) {
                ReceiveBct(aResponse);
            }
        }
    }
} // namespace Zappy::GUI
