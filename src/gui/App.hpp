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
#include "ClientApi.hpp"
#include "EventHandler.hpp"
#include "FrameHandler.hpp"
#include "ServerData.hpp"
#include <unordered_map>

namespace Zappy::GUI {
    class App final : public OgreBites::ApplicationContext
    {
        public:
            // explicit App(std::unique_ptr<Zappy::GUI::ClientApi> client,
            //              const std::string &aWindowName = "UwU Zappy UwU");
            explicit App(const std::string &aWindowName = "UwU Zappy UwU");
            ~App() final;

            App(const App &) = delete;
            App &operator=(const App &) = delete;
            App(App &&) = delete;
            App &operator=(App &&) = delete;

        private:
            void setupLight(Ogre::SceneManager &aSceneManager);
            void setupCamera(Ogre::SceneManager &aSceneManager, Ogre::Vector3 &aCenter);
            Ogre::Vector3f setupMap(Ogre::SceneManager &aSceneManager);
            // std::unique_ptr<Zappy::GUI::ClientApi> _client;
            EventHandler *_cameraHandler;
            FrameHandler *_frameHandler;
    };
} // namespace Zappy::GUI

#endif /* !APP_HPP_ */
