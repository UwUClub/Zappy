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
#include "Inventory.hpp"
#include "MovementHandler.hpp"
#include "Observer.hpp"
#include "PlayerData.hpp"
#include "SceneBuilder.hpp"
#include "ServerData.hpp"

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
                                 Ogre::Vector2(DIMENSION_OVERLAY_DISPLAY_TIME_X, DIMENSION_OVERLAY_DISPLAY_TIME_Y),
                                 "Textbox", RESSOURCE_GROUP_NAME,
                                 Ogre::Vector2(OFFSET_OVERLAY_BUTTON_TIME_X, OFFSET_OVERLAY_BUTTON_TIME_Y));
        this->setReady(true);
    }

    App::~App()
    {
        Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(RESSOURCE_GROUP_NAME);
        this->closeApp();
        this->askDisconnection();
    }

    void App::createButtons()
    {
        _buttons.emplace_back(std::make_unique<Button>(
            "Speed up", std::make_pair(OFFSET_OVERLAY_TIME_X, OFFSET_OVERLAY_BUTTON_1_TIME_Y),
            std::make_pair(DIMENSION_OVERLAY_DISPLAY_TIME_X, DIMENSION_OVERLAY_DISPLAY_TIME_Y), [this] {
                increaseTime();
            }));
        _buttons.emplace_back(std::make_unique<Button>(
            "Speed down", std::make_pair(OFFSET_OVERLAY_TIME_X, OFFSET_OVERLAY_BUTTON_2_TIME_Y),
            std::make_pair(DIMENSION_OVERLAY_DISPLAY_TIME_X, DIMENSION_OVERLAY_DISPLAY_TIME_Y), [this] {
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
            "How to play:\n\nRight click + moving mouse to move camera       Zoom in and out with the mouse wheel.\n"
            "Press the space bar to reset the camera         Left click on a tile to display its content\n"
            "Left click on a player to display its inventory    Left click on an egg to display its inventory\n"
            "Left click on a button to interact with it        Press 'ESC' to quit the game\n"
            "Press left shift and left click to rotate the camera around a central point (can be moved, see above)\n\n"
            "Press any key to dismiss this message\n";
        const auto myWindowHeight = static_cast<float>(this->getRenderWindow()->getHeight());
        const auto myWindowWidth = static_cast<float>(this->getRenderWindow()->getWidth());
        const Ogre::Vector2 myPos = {0, myWindowHeight / 2.0F / 2.0F - 70};
        const Ogre::Vector2 myDimension = {myWindowWidth, 800};

        SceneBuilder::createText(HELP_CONTROLS_OVERLAY, HOW_TO_PLAY_HELP_MESSAGE, HELP_CONTROLS_OVERLAY_PREFIX, myPos,
                                 myDimension, "Textbox", RESSOURCE_GROUP_NAME, Ogre::Vector2(300, 275));
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
                _animatedEntities[mySet.first]->playAnimation("JumpStart", false);
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

    bool App::frameEnded([[maybe_unused]] const Ogre::FrameEvent &aEvent)
    {
        auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);

        for (const auto &myEntityName : _toRemove) {
            try {
                auto *myEntity = myScnMgr->getEntity(myEntityName);

                if (_animatedEntities.find(myEntity) != _animatedEntities.cend()) {
                    _animatedEntities.erase(myEntity);
                }
                if (_moveEntities.find(myEntity) != _moveEntities.cend()) {
                    _moveEntities.erase(myEntity);
                }
                myScnMgr->destroyEntity(myEntityName);
            } catch (const Ogre::Exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        _toRemove.clear();
        return true;
    }
} // namespace Zappy::GUI
