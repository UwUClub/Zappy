/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <string>
namespace Zappy::GUI {
    class Button
    {
        public:
            Button(const std::string &aButtonText);
            ~Button();

        protected:
        private:
    };
} // namespace Zappy::GUI

#endif /* !BUTTON_HPP_ */