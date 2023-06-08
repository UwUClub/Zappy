/*
** EPITECH PROJECT, 2023
** zap
** File description:
** App+Listener
*/

#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/OgreSceneManager.h>
#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreInput.h>
#include <OgrePrerequisites.h>
#include <OgreRenderWindow.h>
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>
#include "App.hpp"

namespace Zappy::GUI {
    void App::getNotified(std::string &aNotification)
    {
        auto myCommand = aNotification.substr(0, aNotification.find_first_of(' '));

        if (_notificationMap.find(myCommand) != _notificationMap.end()) {
            _notificationMap.at(myCommand)(*this, aNotification);
        }
    }

    void App::addPlayer([[maybe_unused]] std::string &aNotification)
    {
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
        auto myServerData = _client.getServerData();
        auto myPlayerData = myServerData._players.back();
        const auto &myPlayerId = myPlayerData.getId();
        const constexpr double myScale = 0.5;
        Ogre::Entity *myEntity = myScnMgr->createEntity(myPlayerId, "Sinbad.mesh");
        Ogre::SceneNode *myNode = myScnMgr->getRootSceneNode()->createChildSceneNode(myPlayerId);

        myNode->attachObject(myEntity);
        myNode->setScale(myScale, myScale, myScale);
        this->setPlayerPosAndOrientation(myPlayerData);
    }

    void App::removePlayer(std::string &aNotification)
    {
        int myIndex = std::stoi(aNotification.substr(4));
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);

        myScnMgr->destroyEntity(std::to_string(myIndex));
    }

    void App::movePlayer(std::string &aNotification)
    {
        auto myServerData = _client.getServerData();
        auto myIndex = aNotification.substr(4);
        auto myPlayerData = std::find_if(myServerData._players.begin(), myServerData._players.end(),
                                         [&myIndex](const PlayerData &aPlayer) {
                                             return aPlayer.getId() == myIndex;
                                         });
        if (myPlayerData == myServerData._players.end()) {
            return;
        }

        this->setPlayerPosAndOrientation(*myPlayerData);
    }

    void App::setPlayerPosAndOrientation(PlayerData &aPlayer)
    {
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
        const auto &myPlayerId = aPlayer.getId();
        static const std::unordered_map<Orientation, Ogre::Real> myOrientationMap = {{Orientation::SOUTH, 0},
                                                                                     {Orientation::EAST, 90},
                                                                                     {Orientation::NORTH, 180},
                                                                                     {Orientation::WEST, 270}};
        Ogre::SceneNode *myNode = myScnMgr->getSceneNode(myPlayerId);

        myNode->setPosition(static_cast<float>(aPlayer.getPosition().first * MAP_OFFSET), PLAYER_Y_POS,
                            static_cast<float>(aPlayer.getPosition().second * MAP_OFFSET));
        myNode->setOrientation(
            Ogre::Quaternion(Ogre::Degree(myOrientationMap.at(aPlayer.getOrientation())), Ogre::Vector3::UNIT_Y));
    }

    void App::displayServerMessage(std::string &aNotification)
    {
        auto myMessage = aNotification.substr(4);

        std::cout << "Server message: " << myMessage << std::endl;
    }
} // namespace Zappy::GUI