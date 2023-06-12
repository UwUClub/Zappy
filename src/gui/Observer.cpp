/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Observer
*/

#include "Observer.hpp"
#include "Mediator.hpp"
#include "ServerData.hpp"

namespace Zappy::GUI {
    Observer::Observer(Mediator &aMediator, ServerData &aServerData)
        : _mediator(aMediator),
          _serverData(aServerData)
    {}

    Observer::~Observer() = default;

} // namespace Zappy::GUI