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

namespace Zappy::GUI {
    class App final : public OgreBites::ApplicationContext
    {
        public:
            explicit App(std::unique_ptr<Zappy::GUI::ClientApi> client,
                         const std::string &aWindowName = "UwU Zappy UwU");
            ~App() final;

            App(const App &) = delete;
            App &operator=(const App &) = delete;
            App(App &&) = delete;
            App &operator=(App &&) = delete;

        private:
            std::unique_ptr<Zappy::GUI::ClientApi> _client;
            std::unique_ptr<Ogre::Root> _root;
    };
} // namespace Zappy::GUI

#endif /* !APP_HPP_ */
