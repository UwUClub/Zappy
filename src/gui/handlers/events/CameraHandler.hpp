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
#include "InputHandler.hpp"

namespace Zappy::GUI {
    class App;
    /**
     * @brief Class used to handle the camera
     * @details This class is used to handle the camera, it is used to move the camera in the scene, refer to the Ogre
     * documentation
     */
    class CameraHandler final : public InputHandler
    {
        public:
            /**
             * @brief Construct a new Camera Handler object
             *
             * @param cameraNode The camera node to use
             * @param center The center of the map
             * @param radius The distance between the camera and the center
             * @param aApp The App object
             */
            CameraHandler(Ogre::SceneNode *cameraNode, Ogre::Vector3 center, Ogre::Real radius, App &aApp);
            ~CameraHandler() final;

            /**
             * @brief Method called when the mouse is moved
             *
             * @param evt The event of the mouse
             * @return a boolean (true)
             */
            bool mouseMoved(const OgreBites::MouseMotionEvent &evt) final;

            /**
             * @brief Method called when the mouse wheel is rolled, see the Ogre documentation for more details
             *
             * @param evt The event of the mouse
             * @return a boolean (true)
             */
            bool mouseWheelRolled(const OgreBites::MouseWheelEvent &evt) final;

            /**
             * @brief Method called when a key is pressed
             *
             * @param evt The event of the key
             * @return a boolean (true)
             */
            bool keyPressed(const OgreBites::KeyboardEvent &evt) final;

        protected:
        private:
            /**
             * @brief Update the camera position
             *
             */
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
