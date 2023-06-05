/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ClickHandler
*/

#ifndef CLICKHANDLER_HPP_
#define CLICKHANDLER_HPP_

#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "ClientApi.hpp"
#include "InputHandler.hpp"

namespace Zappy::GUI {
    class ClickHandler : public InputHandler
    {
        public:
            ClickHandler(Ogre::SceneNode *cameraNode, Ogre::RenderWindow *renderWindow,
                         Ogre::SceneManager *sceneManager, ClientApi &client);
            ~ClickHandler() override;

            bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;

        protected:
            Ogre::SceneNode *getNodeUnderMouse(const Ogre::Vector2 &mousePos);
            Ogre::SceneNode *_cameraNode;
            Ogre::RenderWindow *_renderWindow;
            Ogre::SceneManager *_sceneManager;
    };
} // namespace Zappy::GUI

#endif /* !CLICKHANDLER_HPP_ */
