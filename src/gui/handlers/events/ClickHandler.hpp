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
    class ClickHandler final : public InputHandler
    {
        public:
            /**
             * @brief Construct a new Click Handler object
             *
             * @param cameraNode  The camera node to use
             * @param renderWindow The render window to use
             * @param sceneManager  The scene manager to use
             * @param aApp The App object
             */
            ClickHandler(Ogre::SceneNode *cameraNode, Ogre::RenderWindow *renderWindow,
                         Ogre::SceneManager *sceneManager, App &aApp);
            ~ClickHandler() final;

            /**
             * @brief see the Ogre documentation for more details
             *
             * @param evt The event of the mouse
             * @return a boolean (true)
             */
            bool mousePressed(const OgreBites::MouseButtonEvent &evt) final;

        protected:
            /**
             * @brief Get the Node Under Mouse object
             *
             * @param mousePos The position of the mouse
             * @return Ogre::SceneNode* The node under the mouse
             */
            Ogre::SceneNode *getNodeUnderMouse(const Ogre::Vector2 &mousePos);

            /**
             * @brief Call the callback of the button
             *
             * @param mousePos The position of the mouse
             * @return true if a button has been clicked, false otherwise
             */
            bool execButton(const Ogre::Vector2 &mousePos);
            Ogre::SceneNode *_cameraNode;
            Ogre::RenderWindow *_renderWindow;
            Ogre::SceneManager *_sceneManager;
            std::vector<std::unique_ptr<Button>> &_buttons;
            App &_app;
    };
} // namespace Zappy::GUI

#endif /* !CLICKHANDLER_HPP_ */
