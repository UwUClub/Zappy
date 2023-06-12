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
#include "App.hpp"
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
        const auto &myPlayerId = myPlayerData.getId();
        const constexpr double myScale = 0.5;
        Ogre::Entity *myEntity = myScnMgr->createEntity(myPlayerId, "Sinbad.mesh");
        Ogre::SceneNode *myNode = myScnMgr->getRootSceneNode()->createChildSceneNode(myPlayerId);

        std::cout << "Adding player " << myPlayerId << std::endl;
        myNode->attachObject(myEntity);
        myNode->setScale(myScale, myScale, myScale);
        this->setPlayerPosAndOrientation(myScnMgr, myPlayerData);
    }

    void App::removePlayer(const std::string &aNotification)
    {
        std::istringstream myStream(aNotification);
        std::string myIndex;
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);

        myStream >> myIndex;
        myScnMgr->destroyEntity(myIndex);
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
            std::cerr << "Player " << myIndex << " not found" << std::endl;
            return;
        }
        std::cout << "Moving player " << myIndex << std::endl;
        this->setPlayerPosAndOrientation(myScnMgr, *myPlayerData);
    }

    void App::setPlayerPosAndOrientation(Ogre::SceneManager *aSceneManager, const PlayerData &aPlayer)
    {
        const auto &myPlayerId = aPlayer.getId();
        static const std::unordered_map<Orientation, Ogre::Real> myOrientationMap = {{Orientation::NORTH, 180},
                                                                                     {Orientation::EAST, 90},
                                                                                     {Orientation::SOUTH, 0},
                                                                                     {Orientation::WEST, 270}};
        Ogre::SceneNode *myNode = aSceneManager->getSceneNode(myPlayerId);

        myNode->setPosition(static_cast<float>(aPlayer.getPosition().first * MAP_OFFSET), PLAYER_Y_POS,
                            static_cast<float>(aPlayer.getPosition().second * MAP_OFFSET));
        myNode->setOrientation(
            Ogre::Quaternion(Ogre::Degree(myOrientationMap.at(aPlayer.getOrientation())), Ogre::Vector3::UNIT_Y));
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
} // namespace Zappy::GUI