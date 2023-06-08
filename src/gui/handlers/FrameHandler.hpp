/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** FrameHandler
*/

#ifndef FRAMEHANDLER_HPP_
#define FRAMEHANDLER_HPP_

#include <OGRE/OgreFrameListener.h>
#include <OgreSceneManager.h>
#include "ClientApi.hpp"

namespace Zappy::GUI {
    /**
     * @brief Class used to handle the frames
     * @details This class is used to handle the frames, it is used to update the scene, refer to the Ogre documentation
     */
    class FrameHandler : public Ogre::FrameListener
    {
        public:
            FrameHandler(Ogre::SceneManager *aSceneManager, Zappy::GUI::ClientApi &client);
            ~FrameHandler() override;

            bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
            bool frameStarted(const Ogre::FrameEvent &evt) override;
            bool frameEnded(const Ogre::FrameEvent &evt) override;

        protected:
        private:
            Ogre::SceneManager *_sceneManager;
            Zappy::GUI::ClientApi &_client;
    };
} // namespace Zappy::GUI

#endif /* !FRAMEHANDLER_HPP_ */
