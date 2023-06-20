/*
** EPITECH PROJECT, 2023
** zap
** File description:
** ClientApi+Responses
*/

#include <syncstream>
#include "ClientApi.hpp"
#include "ServerData.hpp"

namespace Zappy::GUI {
    void ClientApi::parseServerResponses()
    {
        static const std::unordered_map<std::string, std::function<void(ClientApi &, std::string)>> myResponses = {
            {"WELCOME", &ClientApi::receiveWelcome}, {"msz", &ClientApi::receiveMsz}, {"bct", &ClientApi::receiveBct},
            {"ko", &ClientApi::receiveError},        {"tna", &ClientApi::receiveTna}, {"sbp", &ClientApi::receiveError},
            {"ppo", &ClientApi::receivePpo},         {"plv", &ClientApi::receivePlv}, {"suc", &ClientApi::receiveError},
            {"sgt", &ClientApi::receiveSgt},         {"sst", &ClientApi::receiveSst}, {"pnw", &ClientApi::receivePnw},
            {"pin", &ClientApi::receivePin},         {"pex", &ClientApi::receivePex}, {"pdr", &ClientApi::receivePdr},
            {"enw", &ClientApi::receiveEnw},         {"edi", &ClientApi::receiveEdi}, {"ebo", &ClientApi::receiveEbo},
            {"pdi", &ClientApi::receivePdi},         {"pgt", &ClientApi::receivePgt}};

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
            std::cout << "Response received: " << myResponse << std::endl;
            _mediator.alert(this, myResponse);
            _readBuffer = _readBuffer.substr(_readBuffer.find('\n') + 1);
        }
    }

    void ClientApi::receiveWelcome(__attribute__((unused)) const std::string &aResponse)
    {
        _writeBuffer += _teamName + "\n";
    }

    void ClientApi::receiveError(const std::string &aResponse)
    {
        std::cerr << "Server error: " << aResponse << std::endl;
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
        int myFood = 0;
        int myLinemate = 0;
        int myDeraumere = 0;
        int mySibur = 0;
        int myMendiane = 0;
        int myPhiras = 0;
        int myThystame = 0;
        std::vector<int> myResources;
        ItemPacket myItemPacket = {};

        myStream >> myX >> myY >> myFood >> myLinemate >> myDeraumere >> mySibur >> myMendiane >> myPhiras
            >> myThystame;
        myResources = {myFood, myLinemate, myDeraumere, mySibur, myMendiane, myPhiras, myThystame};
        myItemPacket.fillItemPacket(myResources);
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
        int myFood = 0;
        int mylinemate = 0;
        int myDeraumere = 0;
        int mySibur = 0;
        int myMendiane = 0;
        int myPhiras = 0;
        int myThystame = 0;
        std::vector<int> myResources;
        ItemPacket myItemPacket = {};

        myStream >> myPlayerId >> myX >> myY >> myFood >> mylinemate >> myDeraumere >> mySibur >> myMendiane >> myPhiras
            >> myThystame;
        myResources = {myFood, mylinemate, myDeraumere, mySibur, myMendiane, myPhiras, myThystame};
        myItemPacket.fillItemPacket(myResources);

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
        std::string myPlayerId;
        int myResourceId = 0;
        std::pair<int, int> const myPos = {};

        myStream >> myPlayerId >> myResourceId;

        auto myPlayerData = std::find_if(_serverData._players.begin(), _serverData._players.end(),
                                         [&myPlayerId](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myPlayerId;
                                         });
        auto myTileData = std::find_if(_serverData._mapTiles.begin(), _serverData._mapTiles.end(),
                                       [&myPos](const TileContent &aTile) {
                                           return std::pair<int, int>(aTile._x, aTile._y) == myPos;
                                       });

        if (myPlayerData != _serverData._players.end()) {
            myPlayerData->setInventory(myResourceId, myPlayerData->getInventory(myResourceId) - 1);
            myTileData->_items.addResources(myResourceId);
        } else {
            throw ClientException("Player not found");
        }
    }

    void ClientApi::receivePex(const std::string &aResponse)
    {
        this->sendCommand("ppo " + aResponse);
    }

    void ClientApi::receivePgt(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        int myResourceId = 0;
        std::pair<int, int> const myPos = {};

        myStream >> myPlayerId >> myResourceId;

        auto myPlayerData = std::find_if(_serverData._players.begin(), _serverData._players.end(),
                                         [&myPlayerId](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myPlayerId;
                                         });
        auto myTileData = std::find_if(_serverData._mapTiles.begin(), _serverData._mapTiles.end(),
                                       [&myPos](const TileContent &aTile) {
                                           return std::pair<int, int>(aTile._x, aTile._y) == myPos;
                                       });

        if (myPlayerData != _serverData._players.end()) {
            myPlayerData->setInventory(myResourceId, myPlayerData->getInventory(myResourceId) + 1);
            myTileData->_items.removeResources(myResourceId);
        } else {
            throw ClientException("Player not found");
        }
    }

    void ClientApi::receivePdi(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;

        myStream >> myPlayerId;

        auto myPlayerData = std::find_if(_serverData._players.begin(), _serverData._players.end(),
                                         [&myPlayerId](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myPlayerId;
                                         });

        if (myPlayerData != _serverData._players.end()) {
            _serverData._players.erase(myPlayerData);
        } else {
            throw ClientException("Player not found");
        }
    }

    void ClientApi::receiveEnw(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        std::string myPlayerId;
        int myEggId = 0;
        unsigned int myX = 0;
        unsigned int myY = 0;

        myStream >> myEggId >> myPlayerId >> myX >> myY;
        auto myPlayerData = std::find_if(_serverData._players.begin(), _serverData._players.end(),
                                         [&myPlayerId](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myPlayerId;
                                         });
        std::string myTeamName = myPlayerData != _serverData._players.end() ? myPlayerData->getTeamName() : "None";

        EggData myEgg(myEggId, std::pair<int, int>(myX, myY), myTeamName);
        _serverData._eggs.push_back(myEgg);
    }

    void ClientApi::receiveEdi(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        int myEggId = 0;

        myStream >> myEggId;

        auto myEggData =
            std::find_if(_serverData._eggs.begin(), _serverData._eggs.end(), [&myEggId](const EggData &aEgg) {
                return aEgg.getId() == myEggId;
            });
        if (myEggData != _serverData._eggs.end()) {
            _serverData._eggs.erase(myEggData);
        } else {
            throw ClientException("Egg not found");
        }
    }

    void ClientApi::receiveEbo(const std::string &aResponse)
    {
        std::istringstream myStream(aResponse);
        int myEggId = 0;

        myStream >> myEggId;

        auto myEggData =
            std::find_if(_serverData._eggs.begin(), _serverData._eggs.end(), [&myEggId](const EggData &aEgg) {
                return aEgg.getId() == myEggId;
            });
        if (myEggData != _serverData._eggs.end()) {
            _serverData._eggs.erase(myEggData);
        } else {
            throw ClientException("Egg not found : " + std::to_string(myEggId));
        }
    }
} // namespace Zappy::GUI
