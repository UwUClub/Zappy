#include "ClientApi.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <syncstream>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <utility>
#include "EggData.hpp"
#include "Observer.hpp"
#include "PlayerData.hpp"
#include "ServerData.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    ClientApi::ClientApi(std::string aAddress, unsigned int aPort, std::string aTeamName, Mediator &aMediator,
                         ServerData &aServerData)
        : Observer(aMediator, ObserverType::CLIENT),
          _address(std::move(aAddress)),
          _port(aPort),
          _teamName(std::move(aTeamName)),
          _connectStatus(-1),
          _serverFd(-1),
          _serverData(aServerData)
    {
        this->setReady(true);
    }

    ClientApi::~ClientApi()
    {
        if (_serverFd != -1) {
            close(_serverFd);
        }
    }

    void ClientApi::run()
    {
        try {
            while (true) {
                this->update();
            }
        } catch (const ClientException &e) {
            std::osyncstream(std::cout) << e.what() << std::endl;
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
        if (_serverFd == -1) {
            throw ClientException("Closed connection");
        }
        if (FD_ISSET(_serverFd, &myReadFds)) {
            readFromServer();
        }
        if (FD_ISSET(_serverFd, &myWriteFds)) {
            writeToServer();
        }
        return 0;
    }

    void ClientApi::disconnect()
    {
        if (_serverFd == -1) {
            return;
        }
        shutdown(_serverFd, SHUT_RDWR);
        close(_serverFd);
        _serverFd = -1;
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

    const ServerData &ClientApi::getServerData() const
    {
        return _serverData;
    }

    struct sockaddr_in ClientApi::getSockaddr(in_addr_t aAddress, unsigned int aPort)
    {
        const constexpr int myBufferSize = 8;
        struct sockaddr_in myAddr = {};

        myAddr.sin_family = AF_INET;
        myAddr.sin_port = htons(static_cast<short unsigned int>(aPort));
        myAddr.sin_addr.s_addr = aAddress;
        memset(&(myAddr.sin_zero), '\0', myBufferSize);
        return myAddr;
    }

    void ClientApi::readFromServer()
    {
        const constexpr int myBufferSize = 4096;
        char myStr[myBufferSize] = {0};
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
        parseServerResponses();
    }

    void ClientApi::writeToServer()
    {
        dprintf(_serverFd, "%s", _writeBuffer.c_str());
        std::cout << "@write: " << _writeBuffer;
        _writeBuffer = "";
    }

    void ClientApi::getNotified(const std::string &aNotification)
    {
        if (aNotification == "Disconnect") {
            this->disconnect();
        }
    }
} // namespace Zappy::GUI