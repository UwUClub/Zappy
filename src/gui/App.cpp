/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** App
*/

#include "App.hpp"
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreFont.h>
#include <OgreInput.h>
#include <OgreLight.h>
#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgrePrerequisites.h>
#include <OgreRenderWindow.h>
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>
#include <OgreSceneNode.h>
#include <algorithm>
#include <functional>
#include <memory>
#include <utility>
#include "Button.hpp"
#include "CameraHandler.hpp"
#include "ClickHandler.hpp"
#include "ClientApi.hpp"
#include "Constexpr.hpp"
#include "ElementFactory.hpp"
#include "InputHandler.hpp"
#include "Observer.hpp"
#include "PlayerData.hpp"
#include "SceneBuilder.hpp"
#include "ServerData.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    App::App(Mediator &aMediator, ServerData &aServerData, const std::string &aWindowName)
        : OgreBites::ApplicationContext(aWindowName),
          Observer(aMediator, ObserverType::APP),
          _cameraHandler(nullptr),
          _clickHandler(nullptr),
          _serverData(aServerData)
    {
        this->initApp();
        auto *myScnMgr = this->getRoot()->createSceneManager("DefaultSceneManager", SCENE_MAN_NAME);

        try {
            this->instantiateApp();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            this->closeApp();
            this->askDisconnection();
            throw AppException(e.what());
        }
        Ogre::RTShader::ShaderGenerator *myShadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        myShadergen->addSceneManager(myScnMgr);

        auto nodeCenterPos = SceneBuilder::buildMap(myScnMgr, _serverData);
        cameraReturn myHandlers = SceneBuilder::buildCamera(myScnMgr, nodeCenterPos, this->getRenderWindow(), *this);
        SceneBuilder::buildLights(myScnMgr, nodeCenterPos);
        SceneBuilder::buildConnectedPlayersAndEggs(myScnMgr, _serverData);

        _cameraHandler.reset(myHandlers.first);
        _clickHandler.reset(myHandlers.second);

        _buttons.emplace_back(std::make_unique<Button>(
            "Speed up", std::make_pair(OFFSET_OVERLAY_TIME_X, OFFSET_OVERLAY_BUTTON_1_TIME_Y), [this] {
                increaseTime();
            }));
        _buttons.emplace_back(std::make_unique<Button>(
            "Speed down", std::make_pair(OFFSET_OVERLAY_TIME_X, OFFSET_OVERLAY_BUTTON_2_TIME_Y), [this] {
                decreaseTime();
            }));
        ElementFactory::createText(BUTTON_OVERLAY, "Current Time: " + std::to_string(_serverData._freq), "Time",
                                   Ogre::Vector2(OFFSET_OVERLAY_TIME_X, OFFSET_OVERLAY_DISPLAY_TIME_Y));
        this->setReady(true);
    }

    App::~App()
    {
        this->closeApp();
        this->askDisconnection();
    }

    void App::instantiateApp()
    {
        const constexpr int myTrueSize = 24;
        const constexpr int myTrueResolution = 96;

        try {
            auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
            myScnMgr->addRenderQueueListener(mOverlaySystem);
            Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./assets", "FileSystem",
                                                                           RESSOURCE_GROUP_NAME);
            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            Ogre::ResourceGroupManager::getSingleton().loadResourceGroup(RESSOURCE_GROUP_NAME);
            myScnMgr->createEntity(PLAYER_MODEL_NAME);
            myScnMgr->createEntity(EGG_MODEL_NAME);
            myScnMgr->createEntity(TILE_MODEL_NAME);

            overlayManager.create(BUTTON_OVERLAY);

            Ogre::FontPtr font = Ogre::FontManager::getSingleton().create(FONT_NAME, RESSOURCE_GROUP_NAME);
            font->setType(Ogre::FontType::FT_TRUETYPE);
            font->setSource("BTTF.ttf");
            font->setTrueTypeSize(myTrueSize);
            font->setTrueTypeResolution(myTrueResolution);
            font->load();
        } catch (const Ogre::Exception &e) {
            throw AppException(e.what());
        }
    }

    void App::windowClosed(Ogre::RenderWindow *aRw)
    {
        this->askDisconnection();
        aRw->destroy();
        this->closeApp();
    }

    const ServerData &App::getServerData() const
    {
        return _serverData;
    }

    std::vector<std::unique_ptr<Button>> &App::getButtons()
    {
        return _buttons;
    }

    void App::askDisconnection()
    {
        _mediator.alert(this, "Disconnect");
    }

    void App::increaseTime()
    {
        auto myCurrentTime = _serverData._freq;
        auto myNewTime = myCurrentTime + MY_TIME_INTERVAL;
        std::string myCommand = "sst " + std::to_string(myNewTime);

        std::cout << myCommand << std::endl;

        _mediator.alert(this, myCommand);
    }

    void App::decreaseTime()
    {
        auto myCurrentTime = _serverData._freq;
        auto myNewTime = myCurrentTime - MY_TIME_INTERVAL;
        std::string myCommand = "sst " + std::to_string(myNewTime);

        std::cout << myCommand << std::endl;
        _mediator.alert(this, myCommand);
    }

} // namespace Zappy::GUI
