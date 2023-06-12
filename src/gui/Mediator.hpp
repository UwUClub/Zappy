/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Mediator
*/

#ifndef MEDIATOR_HPP_
#define MEDIATOR_HPP_

#include <memory>

namespace Zappy::GUI {
    class Observer;
    class ParserData;
    struct ServerData;
    class App;
    class ClientApi;

    class Mediator
    {
        public:
            explicit Mediator(ParserData &parserData);
            ~Mediator();

            void alert(Observer *aObserver, const std::string &aNotification);

            void start();

            Mediator(const Mediator &) = delete;
            Mediator &operator=(const Mediator &) = delete;
            Mediator(Mediator &&) = delete;
            Mediator &operator=(Mediator &&) = delete;

        private:
            std::unique_ptr<ServerData> _serverData;
            std::unique_ptr<App> _app;
            std::unique_ptr<ClientApi> _client;
    };
} // namespace Zappy::GUI

#endif /* !MEDIATOR_HPP_ */
