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
            /**
             * @brief Construct a new Button object
             *
             * @param aButtonText  The text to display on the button
             * @param aPosition  The position of the button
             * @param aDimension The dimension of the background
             * @param aCallback  The callback to call when the button is clicked
             */
            Button(const std::string &aButtonText, const std::pair<float, float> &aPosition,
                   const std::pair<float, float> &aDimension, std::function<void()> aCallback);
            ~Button();

            /**
             * @brief Check if the mouse is on the button
             *
             * @param mousePos The position of the mouse
             * @return true if the mouse is on the button
             * @return false  if the mouse is not on the button
             */
            [[nodiscard]] bool isOnButton(const Ogre::Vector2 &mousePos) const;

            /**
             * @brief Call the callback of the button
             *
             */
            void onClick();

            /**
             * @brief Set the displayed state of the button
             * @param displayed The new displayed state
             */
            void setDisplayed(bool displayed);

        protected:
        private:
            std::pair<int, int> calculateDimensions();
            std::string _buttonText;
            std::pair<float, float> _position;
            std::pair<float, float> _dimensions;
            bool _isDisplayed;
            std::function<void()> _callback;
    };
} // namespace Zappy::GUI

#endif /* !BUTTON_HPP_ */
