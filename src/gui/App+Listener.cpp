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
#include <string>
#include "App.hpp"
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

        SceneBuilder::createPlayer(myScnMgr, myPlayerData);
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
            return;
        }
        SceneBuilder::setPlayerPosAndOrientation(myScnMgr, *myPlayerData);
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
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
        std::istringstream myStream(aNotification);
        std::string myIndex;

        myStream >> myIndex;
        myScnMgr->destroyEntity(EGG_PREFIX_NAME + myIndex);
    }
} // namespace Zappy::GUI