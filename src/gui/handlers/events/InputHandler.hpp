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
    class App;
    /**
     * @brief Class used to handle the mouse events
     * @details Refer to the Ogre documentation
     */
    class InputHandler : public OgreBites::InputListener
    {
        public:
            /**
             * @brief Construct a new Input Handler object
             *
             * @param aApp The App object
             */
            explicit InputHandler(App &aApp);
            ~InputHandler() override;

            /**
             * @brief see the Ogre documentation for more details
             *
             * @param evt The event of the mouse
             * @return true
             * @return false
             */
            bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;

            /**
             * @brief see the Ogre documentation for more details
             *
             * @param evt The event of the mouse
             * @return true
             * @return false
             */
            bool mouseReleased(const OgreBites::MouseButtonEvent &evt) override;

            /**
             * @brief see the Ogre documentation for more details
             *
             * @param evt The event of the mouse
             * @return true
             * @return false
             */
            bool keyPressed(const OgreBites::KeyboardEvent &evt) override;

            /**
             * @brief see the Ogre documentation for more details
             *
             * @param evt The event of the mouse
             * @return true
             * @return false
             */
            bool keyReleased(const OgreBites::KeyboardEvent &evt) override;

        protected:
            bool _isLeftClickPressed;
            bool _isRightClickPressed;
            bool _isShiftPressed;

            App &_app;
    };
} // namespace Zappy::GUI

#endif /* !MOUSEHANDLER_HPP_ */
