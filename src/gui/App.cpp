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
#include "InputHandler.hpp"
#include "PlayerData.hpp"
#include "ServerData.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    App::App(Mediator &aMediator, ServerData &aServerData, const std::string &aWindowName)
        : OgreBites::ApplicationContext(aWindowName),
          Observer(aMediator, aServerData),
          _cameraHandler(nullptr),
          _clickHandler(nullptr)
    {
        this->initApp();
        auto *myRoot = this->getRoot();
        auto *myScnMgr = myRoot->createSceneManager("DefaultSceneManager", SCENE_MAN_NAME);

        try {
            this->instantiateApp();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            this->closeApp();
            this->askDisconnection();
            throw AppException(e.what());
        }

        Ogre::RTShader::ShaderGenerator *myShadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

        auto nodeCenterPos = this->setupMap(myScnMgr);
        this->setupLight(myScnMgr, nodeCenterPos);
        myShadergen->addSceneManager(myScnMgr);
        this->setupCamera(myScnMgr, nodeCenterPos);
        this->setupPlayersAndEggs(myScnMgr);
        _buttons.emplace_back(std::make_unique<Button>("Speed up", std::make_pair(50, 50), [this] {
            increaseTime();
        }));
        _buttons.emplace_back(std::make_unique<Button>("Speed down", std::make_pair(50, 80), [this] {
            decreaseTime();
        }));
        this->displayCurrentTime(std::make_pair(50, 140));
    }

    App::~App()
    {
        this->closeApp();
        this->askDisconnection();
    }

    void App::instantiateApp()
    {
        try {
            auto *myScnMgr = this->getRoot()->getSceneManager(SCENE_MAN_NAME);
            myScnMgr->addRenderQueueListener(mOverlaySystem);
            Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./assets", "FileSystem", "Zappy");
            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
            Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("Zappy");
            myScnMgr->createEntity("Sinbad.mesh");
            myScnMgr->createEntity("Egg.mesh");
            myScnMgr->createEntity("Rock.mesh");

            overlayManager.create(BUTTON_OVERLAY);

            Ogre::FontPtr font = Ogre::FontManager::getSingleton().create(FONT_NAME, "Zappy");
            font->setType(Ogre::FontType::FT_TRUETYPE);
            font->setSource("BTTF.ttf");
            font->setTrueTypeSize(24);
            font->setTrueTypeResolution(96);
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

    void App::askDisconnection()
    {
        _mediator.alert(this, "Disconnect");
    }

    void App::setupLight(Ogre::SceneManager *aSceneManager, Ogre::Vector3 &aCenter)
    {
        Ogre::Light *myLight = aSceneManager->createLight("MainLight");
        myLight->setType(Ogre::Light::LT_DIRECTIONAL);
        myLight->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
        myLight->setSpecularColour(Ogre::ColourValue(1.0, 1.0, 1.0));

        Ogre::SceneNode *myLightNode = aSceneManager->getRootSceneNode()->createChildSceneNode();
        myLightNode->setDirection(Ogre::Vector3(0, -1, 1));
        myLightNode->setPosition(aCenter + Ogre::Vector3(0, 100, 30));
        myLightNode->attachObject(myLight);

        aSceneManager->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    }

    void App::setupCamera(Ogre::SceneManager *aSceneManager, Ogre::Vector3 &aCenterPos)
    {
        auto myServerData = _serverData;
        const auto myMapSize = myServerData._mapSize;
        const constexpr float myBaseRadius = 15;
        const constexpr int myClipDistance = 5;
        const float myRadius = myBaseRadius * (static_cast<float>(std::max(myMapSize.first, myMapSize.second)) / 3);
        Ogre::Vector3 myCamPos(aCenterPos.x, aCenterPos.y + myRadius + myClipDistance, aCenterPos.z + myRadius);
        auto *myRenderWindow = this->getRenderWindow();

        Ogre::SceneNode *myCamNode = aSceneManager->getRootSceneNode()->createChildSceneNode();
        myCamNode->setPosition(myCamPos);

        Ogre::Camera *myCam = aSceneManager->createCamera(CAMERA_NAME);
        myCam->setNearClipDistance(myClipDistance);
        myCam->setAutoAspectRatio(true);

        myCamNode->attachObject(myCam);
        myCamNode->lookAt(aCenterPos, Ogre::Node::TS_WORLD);

        if (myRenderWindow != nullptr) {
            _cameraHandler = std::make_unique<CameraHandler>(myCamNode, aCenterPos, myRadius, *this);
            _clickHandler = std::make_unique<ClickHandler>(myCamNode, myRenderWindow, aSceneManager, *this, _buttons);
            this->addInputListener(_cameraHandler.get());
            this->addInputListener(_clickHandler.get());

            myRenderWindow->addViewport(myCam);
        }
    }

    Ogre::Vector3f App::setupMap(Ogre::SceneManager *aSceneManager)
    {
        auto myServerData = _serverData;
        const auto myMapSize = myServerData._mapSize;
        const constexpr int myTileSize = 1;
        const constexpr Ogre::Real myScale = 0.05F;
        Ogre::Vector3f myCenterPos(0, 0, 0);

        for (unsigned int i = 0; i < myMapSize.first; i++) {
            for (unsigned int j = 0; j < myMapSize.second; j++) {
                std::string myName = std::to_string(i) + " " + std::to_string(j);

                try {
                    Ogre::Entity *myEntity = aSceneManager->createEntity(myName, "Rock.mesh");
                    Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(myName);

                    myNode->attachObject(myEntity);
                    myNode->setPosition(static_cast<float>(i) * (myTileSize * MAP_OFFSET), 0,
                                        static_cast<float>(j) * (myTileSize * MAP_OFFSET));
                    myNode->setScale(myScale, myScale, myScale);
                } catch (Ogre::Exception &e) {
                    std::cerr << e.what() << std::endl;
                    return myCenterPos;
                }
            }
        }
        myCenterPos.x = (static_cast<float>(myMapSize.first) / 2) * (myTileSize * MAP_OFFSET);
        myCenterPos.z = (static_cast<float>(myMapSize.second) / 2) * (myTileSize * MAP_OFFSET);
        return myCenterPos;
    }

    void App::setupPlayersAndEggs(Ogre::SceneManager *aSceneManager)
    {
        auto myServerData = _serverData;
        auto myPlayerData = myServerData._players;
        auto myEggData = myServerData._eggs;

        for (const auto &myPlayer : myPlayerData) {
            const auto &myPlayerId = myPlayer.getId();
            const constexpr double myPlayerScale = 0.5;
            Ogre::Entity *myEntity = aSceneManager->createEntity(myPlayerId, "Sinbad.mesh");
            Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(myPlayerId);

            myNode->setScale(myPlayerScale, myPlayerScale, myPlayerScale);
            myNode->attachObject(myEntity);
            this->setPlayerPosAndOrientation(myPlayer);
        }
        for (const auto &myEgg : myEggData) {
            std::string myEggName = "egg_" + std::to_string(myEgg.getId());
            const constexpr double myEggScale = 0.5;
            Ogre::Entity *myEntity = aSceneManager->createEntity("egg_" + myEggName, "Egg.mesh");
            Ogre::SceneNode *myNode = aSceneManager->getRootSceneNode()->createChildSceneNode(myEggName);

            myNode->setScale(myEggScale, myEggScale, myEggScale);
            myNode->setOrientation(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_X));
            myNode->attachObject(myEntity);
            myNode->setPosition(static_cast<float>(myEgg.getPosition().first * MAP_OFFSET) + EGG_OFFSET_POS, EGG_Y_POS,
                                static_cast<float>(myEgg.getPosition().second * MAP_OFFSET) + EGG_OFFSET_POS);
        }
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

    void App::displayCurrentTime(const std::pair<int, int> &aPosition)
    {
        Ogre::OverlayManager &overlayManager = Ogre::OverlayManager::getSingleton();
        Ogre::Overlay *myOverlay = overlayManager.getByName(BUTTON_OVERLAY);

        auto *myPanel = overlayManager.createOverlayElement("Panel", "Time_Panel");
        auto *myContainer = static_cast<Ogre::OverlayContainer *>(myPanel);
        auto *myText = overlayManager.createOverlayElement("TextArea", "Time_Text");
        auto *myTextArea = static_cast<Ogre::TextAreaOverlayElement *>(myText);
        Ogre::FontPtr myFont = Ogre::FontManager::getSingleton().getByName(FONT_NAME, "Zappy");
        const float myCharHeight = myFont->getGlyphAspectRatio('A') * 17;
        float myTextWidth = 0;
        std::string myTextString = "Current Time: " + std::to_string(_serverData._freq);
        const constexpr float myTextHeight = 1.5F;
        const constexpr float myTextWidthOffset = 1.05F;

        myTextWidth = myCharHeight * static_cast<Ogre::Real>(myTextString.size()) * myTextWidthOffset;
        auto myDimensions = std::make_pair(myTextWidth, myCharHeight * myTextHeight);

        myContainer->setMetricsMode(Ogre::GMM_PIXELS);
        myContainer->setPosition(static_cast<Ogre::Real>(aPosition.first), static_cast<Ogre::Real>(aPosition.second));
        myContainer->setDimensions(myDimensions.first, myDimensions.second);
        myContainer->setMaterialName("BaseWhite");

        myTextArea->setMetricsMode(Ogre::GMM_PIXELS);
        myTextArea->setPosition(0, 0);
        myTextArea->setCaption(myTextString);
        myTextArea->setCharHeight(CHAR_HEIGHT);
        myTextArea->setFontName(FONT_NAME, "Zappy");
        myTextArea->setColourTop(Ogre::ColourValue(1, 0, 1));
        myTextArea->setColourBottom(Ogre::ColourValue(0, 0, 0));

        myContainer->addChild(myTextArea);

        myOverlay->add2D(myContainer);
        myOverlay->show();
    }
} // namespace Zappy::GUI
