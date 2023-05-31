/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** FrameHandler
*/

#ifndef FRAMEHANDLER_HPP_
#define FRAMEHANDLER_HPP_

#include <OGRE/OgreFrameListener.h>

namespace Zappy::GUI {
    class FrameHandler : public Ogre::FrameListener
    {
        public:
            FrameHandler();
            ~FrameHandler() override;

            bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
            bool frameStarted(const Ogre::FrameEvent &evt) override;
            bool frameEnded(const Ogre::FrameEvent &evt) override;

        protected:
        private:
    };
} // namespace Zappy::GUI

#endif /* !FRAMEHANDLER_HPP_ */
