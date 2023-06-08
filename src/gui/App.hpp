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
    /**
     * @brief Main class of the GUI
     *
     * @details This class is the main class of the GUI, it is used to create the window and the scene, and to handle
     * the events using Ogre, it also implements the Subscriber interface to be notified by the ClientApi
     */
    class App final : public OgreBites::ApplicationContext, public Subscriber
    {
        public:
            /**
             * @brief Construct a new App object
             *
             * @param aClient the client api (network)
             * @param aWindowName the name of the window, default value is "UwU Zappy UwU"
             */
            explicit App(Zappy::GUI::ClientApi &aClient, const std::string &aWindowName = WINDOW_NAME);
            ~App() final;

            App(const App &) = delete;
            App &operator=(const App &) = delete;
            App(App &&) = delete;
            App &operator=(App &&) = delete;

            /**
             * @brief Overriden method from Subscriber
             */
            void getNotified(std::string &aNotification) final;

        private:
            /**
             * @brief Setup the light of the scene
             * @param aSceneManager the scene manager
             */
            void setupLight(Ogre::SceneManager *aSceneManager);

            /**
             * @brief Setup the camera of the scene
             * @param aSceneManager the scene manager
             */
            void setupCamera(Ogre::SceneManager *aSceneManager, Ogre::Vector3 &aCenter);
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
            void displayServerMessage(std::string &aNotification);
            /**
             * @brief Setup the map of the scene
             * @param aSceneManager the scene manager
             * @return Ogre::Vector3f the center of the map
             */
            Ogre::Vector3f setupMap(Ogre::SceneManager *aSceneManager);
            /**
             * @brief Add a player to the scene
             * @param aPlayer the playerData of the player to add
             * @param aSceneManager the scene manager
             */
            void addPlayer(std::string &aNotification);
            /**
             * @brief Remove a player from the scene
             * @param aIndex the index of the player to remove
             * @param aSceneManager the scene manager
             */
            void removePlayer(std::string &aNotification);
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
