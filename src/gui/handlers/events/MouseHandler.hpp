/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** MouseHandler
*/

#ifndef MOUSEHANDLER_HPP_
#define MOUSEHANDLER_HPP_

#include <OGRE/Bites/OgreInput.h>

namespace Zappy::GUI {
    class MouseHandler : public OgreBites::InputListener
    {
        public:
            MouseHandler();
            ~MouseHandler() override;

            bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;
            bool mouseReleased(const OgreBites::MouseButtonEvent &evt) override;

        protected:
            bool _isLeftClickPressed;
            bool _isRightClickPressed;
    };
} // namespace Zappy::GUI

#endif /* !MOUSEHANDLER_HPP_ */
