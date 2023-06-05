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
    class Subscriber
    {
        public:
            virtual ~Subscriber() = default;

            virtual void getNotified(std::string &aNotification) = 0;
    };
} // namespace Zappy::GUI

#endif /* !SUBSCRIBER_HPP_ */
