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
#include "ClientApi.hpp"
#include "InputHandler.hpp"

namespace Zappy::GUI {
    const constexpr int BASE_ANGLE = 45;

    class CameraHandler final : public InputHandler
    {
        public:
            CameraHandler(Ogre::SceneNode *cameraNode, Ogre::Vector3 center, Ogre::Real radius, ClientApi &aClient);
            ~CameraHandler() final;

            bool mouseMoved(const OgreBites::MouseMotionEvent &evt) final;
            bool mouseWheelRolled(const OgreBites::MouseWheelEvent &evt) final;
            bool keyPressed(const OgreBites::KeyboardEvent &evt) final;

        protected:
        private:
            void updateCameraPosition();
            Ogre::SceneNode *_cameraNode;
            Ogre::Vector3 _cameraPositionBase;
            Ogre::Vector3 _center;
            Ogre::Vector3 _centerBase;
            Ogre::Real _radius;
            Ogre::Real _radiusBase;
            Ogre::Radian _inclination;
            Ogre::Radian _azimuth;
    };
} // namespace Zappy::GUI

#endif /* !CAMERAHANDLER_HPP_ */
