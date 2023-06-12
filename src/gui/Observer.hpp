/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Subscriber
*/

#ifndef SUBSCRIBER_HPP_
#define SUBSCRIBER_HPP_

#include <string>
namespace Zappy::GUI {
    class Mediator;
    struct ServerData;

    enum class ObserverType
    {
        APP,
        CLIENT
    };
    /**
     * @brief Interface for the Observer pattern
     * @details This interface is used to implement the Observer pattern, it is representing a class that can be
     * notified by a Publisher
     */
    class Observer
    {
        public:
            explicit Observer(Mediator &mediator, const ObserverType &aType);
            virtual ~Observer();

            /**
             * @brief Method called by the Publisher to notify the Subscriber
             * @details This method is called by the Publisher to notify the Subscriber of a change
             * @param aNotification The notification sent by the Publisher
             */
            virtual void getNotified(const std::string &aNotification) = 0;

            /**
             * @brief Alert the observer of an object
             *
             * @param aNotification the notification
             */
            void sendAlert(const std::string &aNotification);

            /**
             * @brief Get the Observer Type object
             *
             * @return ObserverType the type of the observer
             */
            [[nodiscard]] const ObserverType &getObserverType() const;

            /**
             * @brief Check if the observer is ready to listen
             *
             * @return true if it is ready
             * @return false otherwise
             */
            [[nodiscard]] bool isReady() const;

            /**
             * @brief Set the Ready object
             *
             * @param isReady the new value
             */
            void setReady(bool isReady);

        protected:
            Mediator &_mediator;
            const ObserverType _type;
            bool _isReady;
    };
} // namespace Zappy::GUI

#endif /* !SUBSCRIBER_HPP_ */
