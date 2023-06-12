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
#include <OgreSceneManager.h>
#include <functional>
#include <memory>
#include <vector>
#include "Constexpr.hpp"
#include "Observer.hpp"
#include "PlayerData.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    class Mediator;
    class CameraHandler;
    class ClickHandler;
    class Button;
    class PlayerData;
    struct ServerData;

    /**
     * @brief Main class of the GUI
     *
     * @details This class is the main class of the GUI, it is used to create the window and the scene, and to handle
     * the events using Ogre, it also implements the Subscriber interface to be notified by the ClientApi
     */
    class App final : public OgreBites::ApplicationContext, public Observer
    {
        public:
            /**
             * @brief Construct a new App object
             *
             * @param aClient the client api (network)
             * @param aWindowName the name of the window, default value is "UwU Zappy UwU"
             */
            explicit App(Mediator &aMediator, ServerData &aServerData, const std::string &aWindowName = WINDOW_NAME);
            ~App() final;

            App(const App &) = delete;
            App &operator=(const App &) = delete;
            App(App &&) = delete;
            App &operator=(App &&) = delete;

            /**
             * @brief Overriden method from Subscriber
             */
            void getNotified(const std::string &aNotification) final;

            /**
             * @brief Overriden method from OgreBites::ApplicationContext
             *
             * @param aRw the render window
             */
            void windowClosed(Ogre::RenderWindow *aRw) final;

            void askDisconnection();

            [[nodiscard]] const ServerData &getServerData() const;

            std::vector<std::unique_ptr<Button>> &getButtons();

            /**
             * @brief Set the Player Pos And Orientation object
             *
             * @param aPlayer the playerData
             * @param aSceneManager the scene manager
             */
            static void setPlayerPosAndOrientation(Ogre::SceneManager *aSceneManager, const PlayerData &aPlayer);

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
             * @brief Initialize the app
             */
            void instantiateApp();

            /**
             * @brief Move the a player
             *
             * @param aNotification the notification
             * @param aSceneManager the scene manager
             */
            void movePlayer(const std::string &aNotification);
            /**
             * @brief Display a message from the server
             *
             * @param aNotification the notification
             */
            void displayServerMessage(const std::string &aNotification);
            /**
             * @brief Send a command to the server to set the time
             *
             */
            void increaseTime();
            /**
             * @brief Send a command to the server to set the time
             *
             */
            void decreaseTime();
            /**
             * @brief Update the displayed time
             *
             * @param aNotification the notification (not used)
             */
            void updateDisplayedTime(const std::string &aNotification);
            /**
             * @brief Add a player to the scene
             * @param aPlayer the playerData of the player to add
             * @param aSceneManager the scene manager
             */
            void addPlayer(const std::string &aNotification);
            /**
             * @brief Remove a player from the scene
             * @param aIndex the index of the player to remove
             * @param aSceneManager the scene manager
             */
            void removePlayer(const std::string &aNotification);

            std::unique_ptr<CameraHandler> _cameraHandler;
            std::unique_ptr<ClickHandler> _clickHandler;
            std::vector<std::unique_ptr<Button>> _buttons;
            bool _isInitialized;
            const ServerData &_serverData;
            static const inline std::unordered_map<std::string, std::function<void(App &, const std::string &)>>
                _notificationMap = {
                    {"pnw", &App::addPlayer},           {"pdi", &App::removePlayer},
                    {"ppo", &App::movePlayer},          {"smg", &App::displayServerMessage},
                    {"sgt", &App::updateDisplayedTime},
                };
    };
} // namespace Zappy::GUI

#endif /* !APP_HPP_ */
