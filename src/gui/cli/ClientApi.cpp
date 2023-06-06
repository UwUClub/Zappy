#include "ClientApi.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <syncstream>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <utility>
#include "ServerData.hpp"
#include "Subscriber.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    ClientApi::ClientApi(std::string aAddress, unsigned int aPort, std::string aTeamName)
        : _address(std::move(aAddress)),
          _port(aPort),
          _teamName(std::move(aTeamName)),
          _connectStatus(-1),
          _serverFd(-1),
          _serverData(ServerData::getInstance())
    {}

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
        std::cout << "Disconnected from server" << std::endl;
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
        this->notifySubscribers(_readBuffer);
    }

    void ClientApi::writeToServer()
    {
        dprintf(_serverFd, "%s", _writeBuffer.c_str());
        std::cout << "@write: " << _writeBuffer;
        _writeBuffer = "";
    }

    void ClientApi::parseServerResponses()
    {
        static const std::unordered_map<std::string, std::function<void(ClientApi &, std::string)>> myResponses = {
            {"WELCOME", &ClientApi::receiveWelcome}, {"msz", &ClientApi::receiveMsz}, {"bct", &ClientApi::receiveBct},
            {"ko", &ClientApi::receiveError},        {"tna", &ClientApi::receiveTna}, {"sbp", &ClientApi::receiveError},
            {"ppo", &ClientApi::receivePpo},         {"plv", &ClientApi::receivePlv}, {"suc", &ClientApi::receiveError},
            {"sgt", &ClientApi::receiveSgt},         {"sst", &ClientApi::receiveSst}, {"pnw", &ClientApi::receivePnw},
            {"pin", &ClientApi::receivePin},         {"pex", &ClientApi::receivePex}};

        while (_readBuffer.find('\n') != std::string::npos) {
            std::string const myResponse = _readBuffer.substr(0, _readBuffer.find('\n'));
            std::string const myCommand = myResponse.substr(0, myResponse.find(' '));
            std::string const myArgs = myResponse.substr(myResponse.find(' ') + 1);

            if (myResponses.find(myCommand) != myResponses.end()) {
                myResponses.at(myCommand)(*this, myArgs);
            }
            _readBuffer = _readBuffer.substr(_readBuffer.find('\n') + 1);
        }
    }

    void ClientApi::receiveWelcome(__attribute__((unused)) const std::string &aResponse)
    {
        _writeBuffer += _teamName + "\n";
    }

    void ClientApi::receiveError(const std::string &aResponse)
    {
        std::cout << "Server error: " << aResponse << std::endl;
    }

    void ClientApi::receiveMsz(const std::string &aResponse)
    {
        std::string const myX = aResponse.substr(0, aResponse.find(' '));
        std::string const myY = aResponse.substr(aResponse.find(' ') + 1);

        _serverData._mapSize = std::make_pair(std::stoi(myX), std::stoi(myY));
    }

    void ClientApi::receiveBct(const std::string &aResponse)
    {
        ItemPacket myItemPacket = {};
        int myX = 0;
        int myY = 0;
        std::vector<int> myResources;
        std::string myArg = aResponse;

        myX = std::stoi(myArg.substr(0, myArg.find(' ')));
        myY = std::stoi(myArg.substr(myArg.find(' ') + 1, myArg.find(' ')));

        for (int i = 0; i < 7; i++) {
            myResources.push_back(std::stoi(myArg.substr(myArg.find(' ') + 1, myArg.find(' '))));
            myArg = myArg.substr(myArg.find(' ') + 1);
        }
        if (!myArg.empty()) {
            myResources.push_back(std::stoi(myArg));
        }
        myItemPacket.fillItemPacket(myResources);
        _serverData._mapTiles.push_back(
            TileContent(static_cast<unsigned int>(myX), static_cast<unsigned int>(myY), myItemPacket));
    }

    void ClientApi::registerSubscriber(Zappy::GUI::Subscriber &aSubscriber)
    {
        _subscribers.emplace_back(aSubscriber);
    }

    void ClientApi::notifySubscribers(std::string &aNotification)
    {
        for (auto &mySubscriber : _subscribers) {
            mySubscriber.get().getNotified(aNotification);
        }
    }

    void ClientApi::receiveTna(const std::string &aResponse)
    {
        _serverData._teamNames.push_back(aResponse);
    }

    void ClientApi::receivePpo(const std::string &aResponse)
    {
        std::string const &myArg = aResponse;
        std::string const myPlayerId = myArg.substr(0, myArg.find(' '));
        std::string const myX = myArg.substr(myArg.find(' ') + 1, myArg.find(' '));
        std::string const myY = myArg.substr(myArg.find(' ') + 1);

        _serverData._players.at(static_cast<unsigned long>(std::stoi(myPlayerId)))
            .setPosition(static_cast<unsigned int>(std::stoi(myX)), static_cast<unsigned int>(std::stoi(myY)));
    }

    void ClientApi::receivePlv(const std::string &aResponse)
    {
        std::string const &myArg = aResponse;
        std::string const myPlayerId = myArg.substr(0, myArg.find(' '));
        std::string const myLevel = myArg.substr(myArg.find(' ') + 1);

        _serverData._players.at(static_cast<unsigned long>(std::stoi(myPlayerId))).setLevel(std::stoi(myLevel));
    }

    void ClientApi::receivePin(const std::string &aResponse)
    {
        ItemPacket myItemPacket = {};
        int myPlayerId = 0;
        [[maybe_unused]] int myX = 0;
        [[maybe_unused]] int myY = 0;
        std::vector<int> myResources;
        std::string myArg = aResponse;

        myPlayerId = std::stoi(myArg.substr(0, myArg.find(' ')));
        myX = std::stoi(myArg.substr(myArg.find(' ') + 1, myArg.find(' ')));
        myArg = myArg.substr(myArg.find(' ') + 1);
        myY = std::stoi(myArg.substr(myArg.find(' ') + 1, myArg.find(' ')));
        myArg = myArg.substr(myArg.find(' ') + 1);

        for (int i = 0; i < 6; i++) {
            myResources.push_back(std::stoi(myArg.substr(myArg.find(' ') + 1, myArg.find(' '))));
            myArg = myArg.substr(myArg.find(' ') + 1);
        }
        if (!myArg.empty()) {
            myResources.push_back(std::stoi(myArg));
        }
        myItemPacket.fillItemPacket(myResources);
        if (static_cast<unsigned long>(myPlayerId) > _serverData._players.size()) {
            throw Zappy::GUI::ClientApi::ClientException("Player didn't exist");
        }
        _serverData._players.at(static_cast<unsigned long>(myPlayerId)).setInventory(myItemPacket);
    }

    void ClientApi::receivePnw(const std::string &aResponse)
    {
        PlayerData myPlayer = {};
        std::string myArg = aResponse;
        std::string const myPlayerId = myArg.substr(0, myArg.find(' '));
        std::string const myX = myArg.substr(myArg.find(' ') + 1, myArg.find(' '));
        myArg = myArg.substr(myArg.find(' ') + 1);
        std::string const myY = myArg.substr(myArg.find(' ') + 1, myArg.find(' '));
        myArg = myArg.substr(myArg.find(' ') + 1);
        std::string const myOrientation = myArg.substr(myArg.find(' ') + 1, myArg.find(' '));
        myArg = myArg.substr(myArg.find(' ') + 1);
        std::string const myLevel = myArg.substr(myArg.find(' ') + 1, myArg.find(' '));
        myArg = myArg.substr(myArg.find(' ') + 1);
        std::string const myTeamName = myArg.substr(myArg.find(' ') + 1);

        myPlayer.setPosition(static_cast<unsigned int>(std::stoi(myX)), static_cast<unsigned int>(std::stoi(myY)));
        myPlayer.setOrientation((std::stoi(myOrientation)));
        myPlayer.setLevel(std::stoi(myLevel));
        myPlayer.setTeamName(myTeamName);
        std::cout << "Player " << myPlayerId << " joined the game" << std::endl;
        _serverData._players.push_back(myPlayer);
    }

    void ClientApi::receiveSgt(const std::string &aResponse)
    {
        std::string const &myArg = aResponse;
        std::string const myTime = myArg.substr(0, myArg.find(' '));

        _serverData._freq = std::stoi(myTime);
    }

    void ClientApi::receiveSst(const std::string &aResponse)
    {
        std::string const &myArg = aResponse;
        std::string const myTime = myArg.substr(0, myArg.find(' '));

        _serverData._freq = std::stoi(myTime);
    }

    void ClientApi::receivePex(const std::string &aResponse)
    {
        this->sendCommand("ppo " + aResponse);
    }

} // namespace Zappy::GUI
