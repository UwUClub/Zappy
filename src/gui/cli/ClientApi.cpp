#include <arpa/inet.h>
#include <cerrno>
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
#include "ClientApi.hpp"
#include <unordered_map>
#include "ServerData.hpp"
#include "Subscriber.hpp"

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
        std::string mySavedBuffer = _readBuffer;
        parseServerResponses();
        this->notifySubscribers(mySavedBuffer);
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
            {"pin", &ClientApi::receivePin},         {"pdr", &ClientApi::receivePdr}};

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
        std::istringstream myStream(aResponse);
        std::string myX;
        std::string myY;

        myStream >> myX >> myY;
        _serverData._mapSize = std::make_pair(std::stoi(myX), std::stoi(myY));
    }

    void ClientApi::receiveBct(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myX;
        std::string myY;
        std::string food;
        std::string linemate;
        std::string deraumere;
        std::string sibur;
        std::string mendiane;
        std::string phiras;
        std::string thystame;
        std::vector<int> myResource;
        ItemPacket myItemPacket = {};

        myStream >> myX >> myY >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
        myResource = {std::stoi(food),     std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur),
                      std::stoi(mendiane), std::stoi(phiras),   std::stoi(thystame)};
        myItemPacket.fillItemPacket(myResource);
        _serverData._mapTiles.push_back(TileContent(static_cast<unsigned int>(std::stoi(myX)),
                                                    static_cast<unsigned int>(std::stoi(myY)), myItemPacket));
    }

    void ClientApi::receiveTna(const std::string &aResponse)
    {
        _serverData._teamNames.push_back(aResponse);
    }

    void ClientApi::receivePpo(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        std::string myX;
        std::string myY;

        myStream >> myPlayerId >> myX >> myY;

        _serverData._players.at(static_cast<unsigned long>(std::stoi(myPlayerId)))
            .setPosition(static_cast<unsigned int>(std::stoi(myX)), static_cast<unsigned int>(std::stoi(myY)));
    }

    void ClientApi::receivePlv(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        std::string myLevel;

        myStream >> myPlayerId >> myLevel;

        _serverData._players.at(static_cast<unsigned long>(std::stoi(myPlayerId))).setLevel(std::stoi(myLevel));
    }

    void ClientApi::receivePin(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        std::string myX;
        std::string myY;
        std::string food;
        std::string linemate;
        std::string deraumere;
        std::string sibur;
        std::string mendiane;
        std::string phiras;
        std::string thystame;
        std::vector<int> myResource;
        ItemPacket myItemPacket = {};

        myStream >> myPlayerId >> myX >> myY >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras
            >> thystame;
        myResource = {std::stoi(food),     std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur),
                      std::stoi(mendiane), std::stoi(phiras),   std::stoi(thystame)};
        myItemPacket.fillItemPacket(myResource);
        _serverData._players.at(static_cast<unsigned long>(std::stoi(myPlayerId)))
            .setPosition(static_cast<unsigned int>(std::stoi(myX)), static_cast<unsigned int>(std::stoi(myY)));
        _serverData._players.at(static_cast<unsigned long>(std::stoi(myPlayerId))).setInventory(myItemPacket);
    }

    void ClientApi::receivePnw(const std::string &aResponse)
    {
        std::istringstream myIss(aResponse);
        std::string myPlayerId;
        std::string myX;
        std::string myY;
        std::string myOrientation;
        std::string myLevel;
        std::string myTeamName;

        myIss >> myPlayerId >> myX >> myY >> myOrientation >> myLevel >> myTeamName;

        PlayerData myPlayer(myPlayerId);
        myPlayer.setPosition(static_cast<unsigned int>(std::stoi(myX)), static_cast<unsigned int>(std::stoi(myY)));
        myPlayer.setOrientation((std::stoi(myOrientation)));
        myPlayer.setLevel(std::stoi(myLevel));
        myPlayer.setTeamName(myTeamName);
        std::cout << "Player " << myPlayerId << " joined the game" << std::endl;
        _serverData._players.push_back(myPlayer);
    }

    void ClientApi::receiveSgt(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myTime;

        myStream >> myTime;

        _serverData._freq = std::stoi(myTime);
    }

    void ClientApi::receiveSst(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myTime;

        myStream >> myTime;

        _serverData._freq = std::stoi(myTime);
    }

    void ClientApi::receivePdr(const std::string &aResponse) {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        std::string myResourceId;

        myStream >> myPlayerId >> myResourceId;

        int const myPlayerInventory = _serverData._players.at(
                static_cast<unsigned long>(std::stoi(myPlayerId))).getInventory(std::stoi(myResourceId));
        std::pair<int, int> const myPos = _serverData._players.at(
                static_cast<unsigned long>(std::stoi(myPlayerId))).getPosition();

        if (myPlayerInventory > 0) {
            _serverData._players.at(static_cast<unsigned long>(std::stoi(myPlayerId)))
                .setInventory(std::stoi(myResourceId), myPlayerInventory - 1);
        }
        _serverData._mapTiles.at(static_cast<unsigned int>(myPos.second) * _serverData._mapSize.first +
                                         static_cast<unsigned int>(myPos.first))._items.addResources(std::stoi(myResourceId));
    }
} // namespace Zappy::GUI
