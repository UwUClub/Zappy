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
#include "PlayerData.hpp"
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

    void ClientApi::parseServerResponses()
    {
        static const std::unordered_map<std::string, std::function<void(ClientApi &, std::string)>> myResponses = {
            {"WELCOME", &ClientApi::receiveWelcome}, {"msz", &ClientApi::receiveMsz}, {"bct", &ClientApi::receiveBct},
            {"ko", &ClientApi::receiveError},        {"tna", &ClientApi::receiveTna}, {"sbp", &ClientApi::receiveError},
            {"ppo", &ClientApi::receivePpo},         {"plv", &ClientApi::receivePlv}, {"suc", &ClientApi::receiveError},
            {"sgt", &ClientApi::receiveSgt},         {"sst", &ClientApi::receiveSst}, {"pnw", &ClientApi::receivePnw},
            {"pin", &ClientApi::receivePin},         {"pex", &ClientApi::receivePex}, {"pdr", &ClientApi::receivePdr}};

        while (_readBuffer.find('\n') != std::string::npos) {
            std::string myResponse = _readBuffer.substr(0, _readBuffer.find('\n'));
            std::string const myCommand = myResponse.substr(0, myResponse.find(' '));
            std::string const myArgs = myResponse.substr(myResponse.find(' ') + 1);

            if (myResponses.find(myCommand) != myResponses.end()) {
                try {
                    myResponses.at(myCommand)(*this, myArgs);
                } catch (const std::exception &e) {
                    std::osyncstream(std::cout) << e.what() << std::endl;
                }
            }
            this->notifySubscribers(myResponse);
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
        unsigned int myY = 0;
        unsigned int myX = 0;

        myStream >> myX >> myY;
        _serverData._mapSize = std::make_pair(myX, myY);
    }

    void ClientApi::receiveBct(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        unsigned int myX = 0;
        unsigned int myY = 0;
        int food = 0;
        int linemate = 0;
        int deraumere = 0;
        int sibur = 0;
        int mendiane = 0;
        int phiras = 0;
        int thystame = 0;
        std::vector<int> myResource;
        ItemPacket myItemPacket = {};

        myStream >> myX >> myY >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
        myResource = {food, linemate, deraumere, sibur, mendiane, phiras, thystame};
        myItemPacket.fillItemPacket(myResource);
        _serverData._mapTiles.push_back(TileContent(myX, myY, myItemPacket));
    }

    void ClientApi::receiveTna(const std::string &aResponse)
    {
        _serverData._teamNames.push_back(aResponse);
    }

    void ClientApi::receivePpo(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        unsigned int myX = 0;
        unsigned int myY = 0;
        int myOrientation = 0;

        myStream >> myPlayerId >> myX >> myY >> myOrientation;

        auto myPlayerData = std::find_if(_serverData._players.begin(), _serverData._players.end(),
                                         [&myPlayerId](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myPlayerId;
                                         });
        if (myPlayerData != _serverData._players.end()) {
            myPlayerData->setPosition(myX, myY);
            myPlayerData->setOrientation(Orientation(myOrientation));
        } else {
            throw ClientException("Player not found");
        }
    }

    void ClientApi::receivePlv(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        int myLevel = 0;

        myStream >> myPlayerId >> myLevel;

        auto myPlayerData = std::find_if(_serverData._players.begin(), _serverData._players.end(),
                                         [&myPlayerId](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myPlayerId;
                                         });
        if (myPlayerData != _serverData._players.end()) {
            myPlayerData->setLevel(myLevel);
        } else {
            throw ClientException("Player not found");
        }
    }

    void ClientApi::receivePin(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        unsigned int myX = 0;
        unsigned int myY = 0;
        int food = 0;
        int linemate = 0;
        int deraumere = 0;
        int sibur = 0;
        int mendiane = 0;
        int phiras = 0;
        int thystame = 0;
        std::vector<int> myResource;
        ItemPacket myItemPacket = {};

        myStream >> myPlayerId >> myX >> myY >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras
            >> thystame;
        myResource = {food, linemate, deraumere, sibur, mendiane, phiras, thystame};
        myItemPacket.fillItemPacket(myResource);

        auto myPlayerData = std::find_if(_serverData._players.begin(), _serverData._players.end(),
                                         [&myPlayerId](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myPlayerId;
                                         });

        if (myPlayerData != _serverData._players.end()) {
            myPlayerData->setPosition(myX, myY);
            myPlayerData->setInventory(myItemPacket);
        } else {
            throw ClientException("Player not found");
        }
    }

    void ClientApi::receivePnw(const std::string &aResponse)
    {
        std::istringstream myIss(aResponse);
        std::string myPlayerId;
        std::string myTeamName;
        unsigned int myX = 0;
        unsigned int myY = 0;
        int myOrientation = 0;
        int myLevel = 0;

        myIss >> myPlayerId >> myX >> myY >> myOrientation >> myLevel >> myTeamName;

        PlayerData myPlayer(myPlayerId);
        myPlayer.setPosition(myX, myY);
        myPlayer.setOrientation(Orientation(myOrientation));
        myPlayer.setLevel(myLevel);
        myPlayer.setTeamName(myTeamName);
        _serverData._players.push_back(myPlayer);
    }

    void ClientApi::receiveSgt(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        int myTime = 0;

        myStream >> myTime;

        _serverData._freq = myTime;
    }

    void ClientApi::receiveSst(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        int myTime = 0;

        myStream >> myTime;

        _serverData._freq = myTime;
    }

    void ClientApi::receivePdr(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        unsigned long myPlayerId = 0;
        int myResourceId = 0;

        myStream >> myPlayerId >> myResourceId;

        int const myPlayerInventory = _serverData._players.at(myPlayerId).getInventory(myResourceId);
        std::pair<int, int> const myPos = _serverData._players.at(myPlayerId).getPosition();

        if (myPlayerInventory > 0) {
            _serverData._players.at(myPlayerId).setInventory(myResourceId, myPlayerInventory - 1);
        }
        _serverData._mapTiles
            .at(static_cast<unsigned int>(myPos.second) * _serverData._mapSize.first
                + static_cast<unsigned int>(myPos.first))
            ._items.addResources(myResourceId);
    }

    void ClientApi::receivePex(const std::string &aResponse)
    {
        this->sendCommand("ppo " + aResponse);
    }
} // namespace Zappy::GUI
