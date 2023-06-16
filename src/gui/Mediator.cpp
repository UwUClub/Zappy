/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Mediator
*/

#include "Mediator.hpp"
#include <thread>
#include "App.hpp"
#include "ClientApi.hpp"
#include "Observer.hpp"
#include "ParserData.hpp"
#include "ServerData.hpp"

namespace Zappy::GUI {
    Mediator::Mediator(ParserData &parserData)
        : _serverData(std::make_unique<ServerData>()),
          _app(nullptr),
          _client(std::make_unique<ClientApi>(parserData.getAddress(), parserData.getPort(), "GRAPHIC", *this,
                                              *this->_serverData))
    {}

    Mediator::~Mediator() = default;

    void Mediator::alert(Observer *aObserver, const std::string &aNotification)
    {
        const auto myType = aObserver->getObserverType();

        if (_client == nullptr || _app == nullptr) {
            return;
        }

        if (myType == ObserverType::APP && _client->isReady()) {
            _client->getNotified(aNotification);
            std::cout << "Client notified " << aNotification << std::endl;
            return;
        }
        if (myType == ObserverType::CLIENT && _app->isReady()) {
            _app->getNotified(aNotification);
            std::cout << "App notified " << aNotification << std::endl;
            return;
        }
    }

    void Mediator::start()
    {
        try {
            _client->joinGame();
            std::thread myCliThread(&Zappy::GUI::ClientApi::run, *_client);

            _app = std::make_unique<App>(*this, *_serverData);

            _app->getRoot()->startRendering();
            myCliThread.join();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
} // namespace Zappy::GUI
