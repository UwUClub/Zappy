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
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreCommon.h>
#include <OgreFont.h>
#include <OgreInput.h>
#include <OgreRenderWindow.h>
#include <OgreResourceGroupManager.h>
#include <memory>
#include <utility>
#include "AnimationHandler.hpp"
#include "Button.hpp"
#include "CameraHandler.hpp"
#include "ClickHandler.hpp"
#include "Constexpr.hpp"
#include "InputHandler.hpp"
#include "Inventory.hpp"
#include "MovementHandler.hpp"
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
        myScnMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

        auto myNodeCenterPos = SceneBuilder::buildMap(myScnMgr, _serverData);
        cameraReturn myHandlers = SceneBuilder::buildCamera(myScnMgr, myNodeCenterPos, this->getRenderWindow(), *this);
        SceneBuilder::buildLights(myScnMgr, myNodeCenterPos);
        SceneBuilder::buildConnectedPlayersAndEggs(myScnMgr, _serverData, _animatedEntities);

        _cameraHandler.reset(myHandlers.first);
        _clickHandler.reset(myHandlers.second);
        myScnMgr->setSkyBox(true, "Skybox", 50000, true, Ogre::Quaternion::IDENTITY, "Zappy");
        _inventory = std::make_unique<Inventory>(*this);

        this->createButtons();
        this->displayHowToPlayMenu();
        SceneBuilder::createText(BUTTON_OVERLAY, "Current Time: " + std::to_string(_serverData._freq), "Time",
                                 Ogre::Vector2(OFFSET_OVERLAY_TIME_X, OFFSET_OVERLAY_DISPLAY_TIME_Y),
                                 Ogre::Vector2(DIMENSION_OVERLAY_DISPLAY_TIME_X, DIMENSION_OVERLAY_DISPLAY_TIME_Y));
        this->setReady(true);
    }

    App::~App()
    {
        this->closeApp();
        this->askDisconnection();
    }

    void App::createButtons()
    {
        _buttons.emplace_back(std::make_unique<Button>(
            "Speed up", std::make_pair(OFFSET_OVERLAY_TIME_X, OFFSET_OVERLAY_BUTTON_1_TIME_Y),
            std::make_pair(DIMENSION_OVERLAY_BUTTON_1_TIME_X, DIMENSION_OVERLAY_BUTTON_1_TIME_Y), [this] {
                increaseTime();
            }));
        _buttons.emplace_back(std::make_unique<Button>(
            "Speed down", std::make_pair(OFFSET_OVERLAY_TIME_X, OFFSET_OVERLAY_BUTTON_2_TIME_Y),
            std::make_pair(DIMENSION_OVERLAY_BUTTON_2_TIME_X, DIMENSION_OVERLAY_BUTTON_2_TIME_Y), [this] {
                decreaseTime();
            }));
        _buttons.emplace_back(
            std::make_unique<Button>("Next", std::make_pair(1800, 540), std::make_pair(150, 35), [this] {
                _inventory->switchDisplayedPlayer();
            }));
        _buttons.back()->setDisplayed(false);
    }

    void App::CreateMaterial(const std::string &aPath)
    {
        Ogre::TextureManager *myTextureManager = Ogre::TextureManager::getSingletonPtr();
        Ogre::MaterialPtr myMaterial = Ogre::MaterialManager::getSingleton().create(aPath, RESSOURCE_GROUP_NAME);
        Ogre::TexturePtr myTexture = myTextureManager->load(aPath, RESSOURCE_GROUP_NAME);

        Ogre::Technique *myTechnique = myMaterial->getTechnique(0);
        Ogre::Pass *pass = myTechnique->getPass(0);
        pass->createTextureUnitState(myTexture->getName());
    }

    void App::displayHowToPlayMenu()
    {
        static const std::string HOW_TO_PLAY_HELP_MESSAGE =
            "How to play:\nRight click + moving mouse to move camera\n Zoom in and out with the mouse wheel.\n\n "
            "Press "
            "left "
            "shift and left click to rotate the camera around a central point\n Press the "
            "space bar "
            "to reset the camera.\n\n Left click on a tile to display its content\n\n Left click on a player to "
            "display "
            "its "
            "inventory\n Left click on an egg to display its inventory\n Left click on a button to interact with "
            "it\n "
            "Press 'ESC' to quit the game\n"
            "Press any key to dismiss this message\n";
        const auto myWindowHeight = static_cast<float>(this->getRenderWindow()->getHeight());
        const auto myWindowWidth = static_cast<float>(this->getRenderWindow()->getWidth());
        const Ogre::Vector2 myPos = {myWindowWidth / 6, myWindowHeight / 2.0F / 2.0F};
        const Ogre::Vector2 myDimension = {1800, 700};

        SceneBuilder::createText(HELP_CONTROLS_OVERLAY, HOW_TO_PLAY_HELP_MESSAGE, HELP_CONTROLS_OVERLAY_PREFIX, myPos,
                                 myDimension);
    }

    void App::instantiateApp()
    {
        const constexpr int myTrueSize = 24;
        const constexpr int myTrueResolution = 96;

        try {
            auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
            myScnMgr->addRenderQueueListener(mOverlaySystem);
            Ogre::OverlayManager &myOverlayManager = Ogre::OverlayManager::getSingleton();

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./assets", "FileSystem",
                                                                           RESSOURCE_GROUP_NAME);
            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            Ogre::ResourceGroupManager::getSingleton().loadResourceGroup(RESSOURCE_GROUP_NAME);
            this->CreateMaterial("Inventory.png");
            myScnMgr->createEntity(PLAYER_MODEL_NAME);
            myScnMgr->createEntity(EGG_MODEL_NAME);
            myScnMgr->createEntity(TILE_MODEL_NAME);
            myOverlayManager.create(BUTTON_OVERLAY);
            myOverlayManager.create(INVENTORY_OVERLAY);
            myOverlayManager.create(HELP_CONTROLS_OVERLAY);

            Ogre::FontPtr myFont = Ogre::FontManager::getSingleton().create(FONT_NAME, RESSOURCE_GROUP_NAME);

            myFont->setType(Ogre::FontType::FT_TRUETYPE);
            myFont->setSource(FONT_NAME_SRC);
            myFont->setTrueTypeSize(myTrueSize);
            myFont->setTrueTypeResolution(myTrueResolution);
            myFont->load();
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

        _mediator.alert(this, myCommand);
    }

    void App::decreaseTime()
    {
        auto myCurrentTime = _serverData._freq;
        auto myNewTime = myCurrentTime - MY_TIME_INTERVAL;
        std::string myCommand = "sst " + std::to_string(myNewTime);

        _mediator.alert(this, myCommand);
    }

    std::unique_ptr<Inventory> &App::getInventory()
    {
        return _inventory;
    }

    bool App::frameRenderingQueued(const Ogre::FrameEvent &aEvent)
    {
        for (auto &mySet : _animatedEntities) {
            mySet.second->updateAnimation(aEvent.timeSinceLastFrame);
        }
        for (auto &mySet : _moveEntities) {
            if (mySet.second->willTeleport()) {
                mySet.second->teleport();
                continue;
            }
            if (!mySet.second->isMoving()) {
                _animatedEntities[mySet.first]->removeAnimation("RunTop");
                _animatedEntities[mySet.first]->removeAnimation("RunBase");
                continue;
            }
            mySet.second->updateMovement(aEvent.timeSinceLastFrame, _serverData._freq);
        }
        return true;
    }
} // namespace Zappy::GUI
