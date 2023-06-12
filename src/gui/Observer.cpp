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
    Observer::Observer(Mediator &aMediator, const ObserverType &aType)
        : _mediator(aMediator),
          _type(aType),
          _isReady(false)
    {}

    Observer::~Observer() = default;

    const ObserverType &Observer::getObserverType() const
    {
        return _type;
    }

    bool Observer::isReady() const
    {
        return _isReady;
    }

    void Observer::setReady(bool aIsReady)
    {
        _isReady = aIsReady;
    }

} // namespace Zappy::GUI