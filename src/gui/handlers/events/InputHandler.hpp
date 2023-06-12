/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** MouseHandler
*/

#ifndef MOUSEHANDLER_HPP_
#define MOUSEHANDLER_HPP_

#include <OGRE/Bites/OgreInput.h>
#include "ClientApi.hpp"

namespace Zappy::GUI {
    class App;
    /**
     * @brief Class used to handle the mouse events
     * @details Refer to the Ogre documentation
     */
    class InputHandler : public OgreBites::InputListener
    {
        public:
            explicit InputHandler(App &aApp);
            ~InputHandler() override;

            bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;
            bool mouseReleased(const OgreBites::MouseButtonEvent &evt) override;
            bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
            bool keyReleased(const OgreBites::KeyboardEvent &evt) override;

        protected:
            bool _isLeftClickPressed;
            bool _isRightClickPressed;
            bool _isShiftPressed;

            App &_app;
    };
} // namespace Zappy::GUI

#endif /* !MOUSEHANDLER_HPP_ */
