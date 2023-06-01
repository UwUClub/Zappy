/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** KeyHandler
*/

#ifndef KEYHANDLER_HPP_
#define KEYHANDLER_HPP_

#include <OGRE/Bites/OgreInput.h>
#include <OGRE/OgreSceneNode.h>

namespace Zappy::GUI {

    class EventHandler final : public OgreBites::InputListener
    {
        public:
            EventHandler();
            ~EventHandler() final;

            bool keyPressed(const OgreBites::KeyboardEvent &evt) final;
            bool buttonPressed(const OgreBites::ButtonEvent &evt) final;

        private:
    };
} // namespace Zappy::GUI

#endif /* !KEYHANDLER_HPP_ */
