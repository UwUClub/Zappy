/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Observable
*/

#include <vector>
#include "Observer.hpp"

namespace Zappy::GUI {
    class Observable
    {
        public:
            Observable();
            ~Observable();

            void addObserver(Observer *aObserver);
            void removeObserver(Observer *aObserver);
            void notifySubscribers(std::string &aNotification);

        private:
            std::vector<std::reference_wrapper<Observer>> _subscribers;
    };
} // namespace Zappy::GUI