//
// Created by beafowl on 12/06/23.
//

#include <OGRE/Overlay/OgreFont.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OgreOverlay.h>
#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreTechnique.h>
#include <OGRE/OgreTextureManager.h>
#include "Inventory.hpp"
#include "Constexpr.hpp"

namespace Zappy::GUI {
    Inventory::Inventory()
    {
        _food = 0;
        _linemate = 0;
        _deraumere = 0;
        _sibur = 0;
        _mendiane = 0;
        _phiras = 0;
        _thystame = 0;
    }

    int Inventory::parsePlayer(const std::string &aString)
    {
        if (aString.find("player_") != std::string::npos) {
            std::string myNumber = aString.substr(aString.find("player_") + 7);
            return std::stoi(myNumber);
        }
        return -1;
    }

    void Inventory::displayPlayerInventory(int aId, ClientApi &aClientApi)
    {
        std::vector<Ogre::TextAreaOverlayElement *> myTexts;
        Ogre::OverlayManager &myOverlayManager = Ogre::OverlayManager::getSingleton();
        Ogre::Overlay *myOverlay = myOverlayManager.getByName(INVENTORY_OVERLAY);

        Ogre::OverlayContainer *myPanel = static_cast<Ogre::OverlayContainer *>(myOverlayManager.createOverlayElement("Panel", "Inventory_Panel"));
        Ogre::TextAreaOverlayElement *myFoodText = static_cast<Ogre::TextAreaOverlayElement *>(myOverlayManager.createOverlayElement("TextArea", "Food_Text"));
        Ogre::TextAreaOverlayElement *myLinemateText = static_cast<Ogre::TextAreaOverlayElement *>(myOverlayManager.createOverlayElement("TextArea", "Linemate_Text"));
        Ogre::TextAreaOverlayElement *myDeraumereText = static_cast<Ogre::TextAreaOverlayElement *>(myOverlayManager.createOverlayElement("TextArea", "Deraumere_Text"));
        Ogre::TextAreaOverlayElement *mySiburText = static_cast<Ogre::TextAreaOverlayElement *>(myOverlayManager.createOverlayElement("TextArea", "Sibur_Text"));
        Ogre::TextAreaOverlayElement *myMendianeText = static_cast<Ogre::TextAreaOverlayElement *>(myOverlayManager.createOverlayElement("TextArea", "Mendiane_Text"));
        Ogre::TextAreaOverlayElement *myPhirasText = static_cast<Ogre::TextAreaOverlayElement *>(myOverlayManager.createOverlayElement("TextArea", "Phiras_Text"));
        Ogre::TextAreaOverlayElement *myThystameText = static_cast<Ogre::TextAreaOverlayElement *>(myOverlayManager.createOverlayElement("TextArea", "Thystame_Text"));

        myTexts.push_back(myFoodText);
        myTexts.push_back(myLinemateText);
        myTexts.push_back(myDeraumereText);
        myTexts.push_back(mySiburText);
        myTexts.push_back(myMendianeText);
        myTexts.push_back(myPhirasText);
        myTexts.push_back(myThystameText);

        myPanel->setMetricsMode(Ogre::GMM_PIXELS);
        myPanel->setPosition(0, 0);
        myPanel->setDimensions(100, 100);
        this->CreateMaterial("Rock_diffuse.png");
        myPanel->setMaterialName("Rock_diffuse.png", "Zappy");
        myOverlay->add2D(myPanel);

        for (auto &myText : myTexts) {
            myText->setMetricsMode(Ogre::GMM_PIXELS);
            myText->setDimensions(100, 100);
            myText->setFontName(FONT_NAME, "Zappy");
            myText->setCharHeight(CHAR_HEIGHT);
            myText->setColourBottom(Ogre::ColourValue::Black);
            myText->setColourTop(Ogre::ColourValue::Black);
            myPanel->addChild(myText);
        }

        ItemPacket myInventory = this->getInventoryPlayer(aId, aClientApi);
        //myTexts[0]->setCaption(static_cast<Ogre::DisplayString>(myInventory._food));
        //myTexts[1]->setCaption(myInventory._deraumere);
        myTexts[2]->setCaption("Deraumere:");
        myTexts[3]->setCaption("Sibur:");
        myTexts[4]->setCaption("Mendiane:");
        myTexts[5]->setCaption("Phiras:");
        myTexts[6]->setCaption("Thystame:");

        myTexts[0]->setPosition(0, 0);
        myTexts[1]->setPosition(0, 20);
        myTexts[2]->setPosition(0, 40);
        myTexts[3]->setPosition(0, 60);
        myTexts[4]->setPosition(0, 80);
        myTexts[5]->setPosition(0, 100);
        myTexts[6]->setPosition(0, 120);

        myPanel->show();
    }

    ItemPacket Inventory::getInventoryPlayer(int aId, ClientApi &aClientApi)
    {
        ItemPacket myPacket;
        ServerData myData = aClientApi.getServerData();

        auto myPlayerData = std::find_if(myData._players.begin(), myData._players.end(),
                                         [&aId](const PlayerData &aPlayer) {
                                             return std::stoi(aPlayer.getId()) == aId;
                                         });

        if (myPlayerData != myData._players.end()) {
            myPacket._food = myPlayerData->getInventory(0);
            myPacket._linemate = myPlayerData->getInventory(1);
            myPacket._deraumere = myPlayerData->getInventory(2);
            myPacket._sibur = myPlayerData->getInventory(3);
            myPacket._mendiane = myPlayerData->getInventory(4);
            myPacket._phiras = myPlayerData->getInventory(5);
            myPacket._thystame = myPlayerData->getInventory(6);
        }
        return myPacket;
    }

    void Inventory::CreateMaterial(const std::string &aPath)
    {
        Ogre::TextureManager* myTextureManager = Ogre::TextureManager::getSingletonPtr();
        Ogre::MaterialPtr myMaterial = Ogre::MaterialManager::getSingleton().create(aPath, "Zappy");
        Ogre::TexturePtr myTexture = myTextureManager->load(aPath, "Zappy");

        Ogre::Technique* myTechnique = myMaterial->getTechnique(0);
        Ogre::Pass* pass = myTechnique->getPass(0);
        pass->createTextureUnitState(myTexture->getName());
    }

    Ogre::OverlayContainer *Inventory::CreateMaterial(const std::string &aName, const std::string &aPath, Ogre::OverlayContainer *aContainer, Ogre::Vector2 aPosition, Ogre::Vector2 aDimensions)
    {
        Ogre::TextureManager* myTextureManager = Ogre::TextureManager::getSingletonPtr();
        Ogre::MaterialPtr myMaterial = Ogre::MaterialManager::getSingleton().create(aName, "Zappy");
        Ogre::TexturePtr myTexture = myTextureManager->load(aPath, "Zappy");

        Ogre::Technique* myTechnique = myMaterial->getTechnique(0);
        Ogre::Pass* pass = myTechnique->getPass(0);
        pass->createTextureUnitState(myTexture->getName());

        aContainer->setMaterialName(aName);
        aContainer->setMetricsMode(Ogre::GMM_PIXELS);
        aContainer->setPosition(aPosition.x, aPosition.y);
        aContainer->setDimensions(aDimensions.x, aDimensions.y);
        return aContainer;
    }
} // namespace Zappy::GUI