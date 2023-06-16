/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Observable
*/

#include <vector>
#include "Observer.hpp"

namespace Zappy::GUI {
    /**
     * @brief Observable class
     * @details Observable class for the observer pattern
     */
    class Observable
    {
        public:
            Observable();
            ~Observable();

            /**
             * @brief add an observer to the list
             * @param aObserver the observer to add
             */
            void addObserver(Observer *aObserver);
            /**
             * @brief remove an observer from the list
             * @param aObserver the observer to remove
             */
            void removeObserver(Observer *aObserver);
            /**
             * @brief notify all the observers
             * @param aNotification the notification to send
             */
            void notifySubscribers(const std::string &aNotification);

        private:
            std::vector<std::reference_wrapper<Observer>> _subscribers;
    };
} // namespace Zappy::GUI