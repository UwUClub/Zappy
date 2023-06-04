/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** CameraHandler
*/

#ifndef CAMERAHANDLER_HPP_
#define CAMERAHANDLER_HPP_

#include <OGRE/Bites/OgreInput.h>
#include <OGRE/OgreSceneNode.h>
#include <OgreMath.h>
#include <OgrePrerequisites.h>
#include <OgreRenderWindow.h>
#include "MouseHandler.hpp"

namespace Zappy::GUI {
    const Ogre::Radian BASE_INCLINATION = Ogre::Radian(45);
    const Ogre::Radian BASE_AZIMUTH = Ogre::Radian(45);

    class EventHandler final : public MouseHandler
    {
        public:
            EventHandler(Ogre::SceneNode *cameraNode, Ogre::Vector3 center, Ogre::Real radius,
                         Ogre::SceneManager &aSceneManager, Ogre::RenderWindow *aRenderWindow);
            ~EventHandler() final;

            bool mouseMoved(const OgreBites::MouseMotionEvent &evt) final;
            bool mousePressed(const OgreBites::MouseButtonEvent &evt) final;
            bool mouseReleased(const OgreBites::MouseButtonEvent &evt) final;
            bool mouseWheelRolled(const OgreBites::MouseWheelEvent &evt) final;
            bool keyPressed(const OgreBites::KeyboardEvent &evt) final;
            bool keyReleased(const OgreBites::KeyboardEvent &evt) final;

        protected:
        private:
            Ogre::SceneNode *getNodeUnderMouse(const Ogre::Vector2 &mousePos);
            void updateCameraPosition();
            bool _isShiftPressed;
            Ogre::SceneNode *_cameraNode;
            Ogre::Vector3 _cameraPositionBase;
            Ogre::Vector3 _center;
            Ogre::Real _radius;
            Ogre::Real _radiusBase;
            Ogre::Radian _inclination;
            Ogre::Radian _azimuth;
            Ogre::SceneManager &_sceneManager;
            Ogre::RenderWindow *_renderWindow;
    };
} // namespace Zappy::GUI

#endif /* !CAMERAHANDLER_HPP_ */
