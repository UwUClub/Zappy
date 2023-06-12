/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Observable
*/

#include "Observable.hpp"
#include <algorithm>

namespace Zappy::GUI {
    Observable::Observable() = default;

    Observable::~Observable() = default;

    void Observable::addObserver(Observer *aObserver)
    {
        _subscribers.emplace_back(*aObserver);
    }

    void Observable::removeObserver(Observer *aObserver)
    {
        auto myIterator = std::find_if(_subscribers.begin(), _subscribers.end(),
                                       [aObserver](std::reference_wrapper<Observer> &aSubscriber) {
                                           return &aSubscriber.get() == aObserver;
                                       });

        if (myIterator != _subscribers.end()) {
            _subscribers.erase(myIterator);
        }
    }

    void Observable::notifySubscribers(std::string &aNotification)
    {
        for (auto &subscriber : _subscribers) {
            subscriber.get().getNotified(aNotification);
        }
    }
} // namespace Zappy::GUI