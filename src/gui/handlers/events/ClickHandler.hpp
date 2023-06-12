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
#include "InputHandler.hpp"

namespace Zappy::GUI {
    class App;
    class Button;
    /**
     * @brief Class used to handle the mouse clicks
     * @details This class is used to handle the mouse clicks, it is used to select a node in the scene, refer to the
     * Ogre documentation
     */
    class ClickHandler : public InputHandler
    {
        public:
            ClickHandler(Ogre::SceneNode *cameraNode, Ogre::RenderWindow *renderWindow,
                         Ogre::SceneManager *sceneManager, App &aApp);
            ~ClickHandler() override;

            bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;

        protected:
            Ogre::SceneNode *getNodeUnderMouse(const Ogre::Vector2 &mousePos);
            bool execButton(const Ogre::Vector2 &mousePos);
            Ogre::SceneNode *_cameraNode;
            Ogre::RenderWindow *_renderWindow;
            Ogre::SceneManager *_sceneManager;
            std::vector<std::unique_ptr<Button>> &_buttons;
    };
} // namespace Zappy::GUI

#endif /* !CLICKHANDLER_HPP_ */
