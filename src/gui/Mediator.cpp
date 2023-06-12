/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Mediator
*/

#include "Mediator.hpp"
#include "App.hpp"
#include "ClientApi.hpp"
#include "Observer.hpp"
#include "ParserData.hpp"

namespace Zappy::GUI {
    Mediator::Mediator(ParserData &parserData)
        : _serverData(std::make_unique<ServerData>()),
          _app(std::make_unique<App>(*this, *this->_serverData)),
          _client(std::make_unique<ClientApi>(parserData.getAddress(), parserData.getPort(), "GRAPHIC", *this,
                                              *this->_serverData))
    {}

    Mediator::~Mediator() = default;

    void Mediator::alert(Observer *aObserver, const std::string &aNotification)
    {
        if (aObserver == _app.get()) {
            _client->getNotified(aNotification);
            return;
        }
        if (aObserver == _client.get()) {
            _app->getNotified(aNotification);
            return;
        }
    }

    void Mediator::start()
    {
        try {
            _client->joinGame();
            std::thread myCliThread(&Zappy::GUI::ClientApi::run, &_client);

            _app->getRoot()->startRendering();
            myCliThread.join();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
} // namespace Zappy::GUI
