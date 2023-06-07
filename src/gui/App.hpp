/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** App
*/

#ifndef APP_HPP_
#define APP_HPP_
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OgreRoot.h>
#include <memory>
#include "CameraHandler.hpp"
#include "ClickHandler.hpp"
#include "ClientApi.hpp"
#include "Constexpr.hpp"
#include "FrameHandler.hpp"
#include "InputHandler.hpp"
#include "PlayerData.hpp"
#include "ServerData.hpp"
#include "Subscriber.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    class App final : public OgreBites::ApplicationContext, public Subscriber
    {
        public:
            explicit App(Zappy::GUI::ClientApi &client, const std::string &aWindowName = WINDOW_NAME);
            ~App() final;

            App(const App &) = delete;
            App &operator=(const App &) = delete;
            App(App &&) = delete;
            App &operator=(App &&) = delete;

            void getNotified(std::string &aNotification) final;
            bool windowClosing(Ogre::RenderWindow *aRenderWindow) final;

        private:
            void setupLight(Ogre::SceneManager *aSceneManager);
            void setupCamera(Ogre::SceneManager *aSceneManager, Ogre::Vector3 &aCenter);
            Ogre::Vector3f setupMap(Ogre::SceneManager *aSceneManager);
            void addPlayer(PlayerData &aPlayer, Ogre::SceneManager *aSceneManager);
            static void removePlayer(int aIndex, Ogre::SceneManager *aSceneManager);
            /**
             * @brief Move the a player
             *
             * @param aIndex the index of the player
             * @param aSceneManager the scene manager
             */
            void movePlayer(int aIndex, Ogre::SceneManager *aSceneManager);
            /**
             * @brief Set the Player Pos And Orientation object
             *
             * @param aPlayer the playerData
             * @param aSceneManager the scene manager
             */
            static void setPlayerPosAndOrientation(PlayerData &aPlayer, Ogre::SceneManager *aSceneManager);
            Zappy::GUI::ClientApi &_client;
            std::unique_ptr<CameraHandler> _cameraHandler;
            std::unique_ptr<FrameHandler> _frameHandler;
            std::unique_ptr<ClickHandler> _clickHandler;
    };
} // namespace Zappy::GUI

#endif /* !APP_HPP_ */
