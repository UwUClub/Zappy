/*
** EPITECH PROJECT, 2023
** zap
** File description:
** App+Listener
*/

#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreInput.h>
#include <OgrePrerequisites.h>
#include <OgreRenderWindow.h>
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>
#include <OgreTextAreaOverlayElement.h>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include "AnimationHandler.hpp"
#include "App.hpp"
#include "Constexpr.hpp"
#include "MovementHandler.hpp"
#include "SceneBuilder.hpp"
#include "ServerData.hpp"

namespace Zappy::GUI {
    void App::getNotified(const std::string &aNotification)
    {
        auto myCommand = aNotification.substr(0, aNotification.find_first_of(' '));
        auto myArgs = aNotification.substr(aNotification.find_first_of(' ') + 1);

        if (_notificationMap.find(myCommand) != _notificationMap.end()) {
            _notificationMap.at(myCommand)(*this, myArgs);
        }
    }

    void App::addPlayer([[maybe_unused]] const std::string &aNotification)
    {
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
        auto myPlayerData = _serverData._players.back();

        SceneBuilder::createPlayer(myScnMgr, myPlayerData, _animatedEntities, _moveEntities, _serverData._mapSize);
    }

    void App::removePlayer(const std::string &aNotification)
    {
        std::istringstream myStream(aNotification);
        std::string myIndex;

        myStream >> myIndex;
        _toRemove.push_back(PLAYER_PREFIX_NAME + myIndex);
    }

    void App::movePlayer(const std::string &aNotification)
    {
        std::istringstream myStream(aNotification);
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
        std::string myIndex;

        myStream >> myIndex;
        auto myPlayerData = std::find_if(_serverData._players.cbegin(), _serverData._players.cend(),
                                         [&myIndex](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myIndex;
                                         });

        if (myPlayerData == _serverData._players.cend()) {
            return;
        }
        auto *myPlayer = myScnMgr->getEntity(PLAYER_PREFIX_NAME + myIndex);
        Ogre::Vector3 myArrivalPoint(static_cast<float>(myPlayerData->getPosition().first * MAP_OFFSET), PLAYER_Y_POS,
                                     static_cast<float>(myPlayerData->getPosition().second * MAP_OFFSET));

        _animatedEntities[myPlayer]->playAnimation("RunBase");
        _animatedEntities[myPlayer]->playAnimation("RunTop");
        _moveEntities[myPlayer]->setArrivalPoint(myArrivalPoint);
        SceneBuilder::setPlayerOrientation(myScnMgr, *myPlayerData);
    }

    void App::displayServerMessage(const std::string &aNotification)
    {
        std::cout << "Server message: " << aNotification << std::endl;
    }

    void App::updateDisplayedTime([[maybe_unused]] const std::string &aNotification)
    {
        try {
            auto *myTextArea = static_cast<Ogre::TextAreaOverlayElement *>(
                Ogre::OverlayManager::getSingleton().getOverlayElement("Time_Text"));
            std::string myTextString = "Current Time: " + std::to_string(_serverData._freq);

            myTextArea->setCaption(myTextString);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void App::addEgg(const std::string &aNotification)
    {
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
        std::istringstream myStream(aNotification);
        int myIndex = 0;

        myStream >> myIndex;
        auto myEggData =
            std::find_if(_serverData._eggs.cbegin(), _serverData._eggs.cend(), [&myIndex](const EggData &aEgg) {
                return aEgg.getId() == myIndex;
            });
        if (myEggData == _serverData._eggs.cend()) {
            return;
        }
        SceneBuilder::createEgg(myScnMgr, *myEggData);
    }

    void App::removeEgg(const std::string &aNotification)
    {
        std::istringstream myStream(aNotification);
        std::string myIndex;

        myStream >> myIndex;
        _toRemove.push_back(EGG_PREFIX_NAME + myIndex);
    }

    void App::startedIncantation(const std::string &aNotification)
    {
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
        std::istringstream myStream(aNotification);
        int myX = 0;
        int myY = 0;
        int myLevel = 0;
        std::string myIndex;

        myStream >> myX >> myY >> myLevel;
        while (myStream >> myIndex) {
            try {
                auto *myPlayer = myScnMgr->getEntity(PLAYER_PREFIX_NAME + myIndex);
                _animatedEntities[myPlayer]->playAnimation("Dance");
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
                continue;
            }
        }
    }

    void App::stoppedIncantation(const std::string &aNotification)
    {
        std::istringstream myStream(aNotification);
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
        unsigned int myX = 0;
        unsigned int myY = 0;

        myStream >> myX >> myY;
        for (const auto &myPlayerData : _serverData._players) {
            if (myPlayerData.getPosition().first != myX && myPlayerData.getPosition().second != myY) {
                continue;
            }
            try {
                auto *myPlayer = myScnMgr->getEntity(PLAYER_PREFIX_NAME + myPlayerData.getId());
                _animatedEntities[myPlayer]->removeAnimation("Dance");
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
                continue;
            }
        }
    }

    void App::droppedRessources(const std::string &aNotification)
    {
        std::istringstream myStream(aNotification);
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);

        std::string myId;

        myStream >> myId;

        try {
            auto *myPlayer = myScnMgr->getEntity(PLAYER_PREFIX_NAME + myId);
            _animatedEntities[myPlayer]->playAnimation("SliceVertical", false);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
    }

    void App::playerExpulsion(const std::string &aNotification)
    {
        std::istringstream myStream(aNotification);
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);

        std::string myId;

        myStream >> myId;

        try {
            auto *myPlayer = myScnMgr->getEntity(PLAYER_PREFIX_NAME + myId);
            _animatedEntities[myPlayer]->playAnimation("SliceHorizontal", false);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
    }
} // namespace Zappy::GUI
