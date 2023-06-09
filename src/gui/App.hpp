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
#include "Button.hpp"
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
            class AppException : public std::exception
            {
                public:
                    explicit AppException(const std::string &aMessage)
                        : _message(aMessage)
                    {}
                    ~AppException() override = default;

                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };
            /**
             * @brief Setup the light of the scene
             * @param aSceneManager the scene manager
             */
            void setupLight(Ogre::SceneManager *aSceneManager, Ogre::Vector3 &aCenter);

            /**
             * @brief Initialize the app
             */
            void instantiateApp();

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
            void setPlayerPosAndOrientation(const PlayerData &aPlayer);
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
            /**
             * @brief Setup the map of the scene
             * @param aSceneManager the scene manager
             * @return Ogre::Vector3f the center of the map
             */
            Ogre::Vector3f setupMap(Ogre::SceneManager *aSceneManager);
            /**
             * @brief Setup the players and eggs of the scene already on the map
             *
             * @param aSceneManager the scene manager
             */
            void setupPlayersAndEggs(Ogre::SceneManager *aSceneManager);
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
            std::vector<std::unique_ptr<Button>> _buttons;

            static const inline std::unordered_map<std::string, std::function<void(App &, std::string &)>>
                _notificationMap = {{"pnw", &App::addPlayer},
                                    {"pdi", &App::removePlayer},
                                    {"ppo", &App::movePlayer},
                                    {"smg", &App::displayServerMessage}};
    };
} // namespace Zappy::GUI

#endif /* !APP_HPP_ */
