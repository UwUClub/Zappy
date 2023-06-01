/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** App
*/

#include "App.hpp"

namespace Zappy::GUI {
    App::App(std::unique_ptr<Zappy::GUI::ClientApi> client, const std::string &aWindowName)
        : OgreBites::ApplicationContext(aWindowName),
          _client(std::move(client))
    {
        this->initApp();
        _client->joinGame();
    }

    App::~App()
    {
        this->closeApp();
    }
} // namespace Zappy::GUI
