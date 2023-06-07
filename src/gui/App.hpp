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
#include <functional>
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
            void addPlayer(std::string &aNotification);
            void removePlayer(std::string &aNotification);
            /**
             * @brief Move the a player
             *
             * @param aNotification the notification
             * @param aSceneManager the scene manager
             */
            void movePlayer(std::string &aNotification);
            /**
             * @brief Set the Player Pos And Orientation object
             *
             * @param aPlayer the playerData
             * @param aSceneManager the scene manager
             */
            void setPlayerPosAndOrientation(PlayerData &aPlayer);
            /**
             * @brief Display a message from the server
             *
             * @param aNotification the notification
             */
            void displayServerMessage(std::string &aNotification);
            /**
             * @brief Send a command to the server to set the time
             *
             * @param aTime the time
             */
            void setTime(int aTime);
            Zappy::GUI::ClientApi &_client;
            std::unique_ptr<CameraHandler> _cameraHandler;
            std::unique_ptr<FrameHandler> _frameHandler;
            std::unique_ptr<ClickHandler> _clickHandler;

            static const inline std::unordered_map<std::string, std::function<void(App &, std::string &)>>
                _notificationMap = {{"pnw", &App::addPlayer},
                                    {"pdi", &App::removePlayer},
                                    {"ppo", &App::movePlayer},
                                    {"message", &App::displayServerMessage}};
    };
} // namespace Zappy::GUI

#endif /* !APP_HPP_ */
