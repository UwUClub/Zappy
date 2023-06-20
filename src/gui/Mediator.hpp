/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Mediator
*/

#ifndef MEDIATOR_HPP_
#define MEDIATOR_HPP_

#include <memory>
#include "ClientApi.hpp"

namespace Zappy::GUI {
    class Observer;
    class ParserData;
    struct ServerData;
    class App;

    class Mediator
    {
        public:
            /**
             * @brief Construct a new Mediator object
             *
             * @param parserData The parser data received from the CLI
             */
            explicit Mediator(ParserData &parserData);
            ~Mediator();

            /**
             * @brief Alert the observer of an object
             *
             * @param aObserver the observer that is alerting
             * @param aNotification the notification
             */
            void alert(Observer *aObserver, const std::string &aNotification);

            /**
             * @brief Start the game loop
             *
             */
            void start();

            Mediator(const Mediator &) = delete;
            Mediator &operator=(const Mediator &) = delete;
            Mediator(Mediator &&) = delete;
            Mediator &operator=(Mediator &&) = delete;

        private:
            std::unique_ptr<ServerData> _serverData;
            std::unique_ptr<App> _app;
            ClientApi _client;
    };
} // namespace Zappy::GUI

#endif /* !MEDIATOR_HPP_ */
