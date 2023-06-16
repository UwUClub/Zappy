/*
** EPITECH PROJECT, 2023
** zap
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <OgrePrerequisites.h>
#include <functional>
#include <string>

namespace Zappy::GUI {
    class Button
    {
        public:
            Button(const std::string &aButtonText, const std::pair<int, int> &aPosition,
                   std::function<void()> aCallback);
            ~Button();

            [[nodiscard]] const std::pair<int, int> &getPosition() const;
            [[nodiscard]] const std::pair<int, int> &getDimensions() const;
            [[nodiscard]] const std::string &getButtonText() const;

            [[nodiscard]] bool isOnButton(const Ogre::Vector2 &mousePos) const;
            void onClick();

        protected:
        private:
            std::pair<int, int> calculateDimensions();
            std::string _buttonText;
            std::pair<int, int> _position;
            std::pair<int, int> _dimensions;
            std::function<void()> _callback;
    };
} // namespace Zappy::GUI

#endif /* !BUTTON_HPP_ */