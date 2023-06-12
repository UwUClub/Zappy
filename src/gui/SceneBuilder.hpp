/*
** EPITECH PROJECT, 2023
** zap
** File description:
** SceneBuilder
*/

#ifndef SCENEBUILDER_HPP_
#define SCENEBUILDER_HPP_

#include <OgrePrerequisites.h>

namespace Ogre {
    class SceneManager;
    class RenderWindow;
} // namespace Ogre

namespace Zappy::GUI {
    struct ServerData;
    class CameraHandler;
    class ClickHandler;
    class App;

    using cameraReturn = std::pair<CameraHandler *, ClickHandler *>;

    class SceneBuilder
    {
        public:
            SceneBuilder() = delete;
            ~SceneBuilder() = delete;

            static void buildLights(Ogre::SceneManager *aSceneManager, const Ogre::Vector3 &aCenter);
            static Ogre::Vector3f buildMap(Ogre::SceneManager *aSceneManager, const ServerData &aServerData);
            static cameraReturn buildCamera(Ogre::SceneManager *aSceneManager, const Ogre::Vector3 &aCenter,
                                            Ogre::RenderWindow *aRenderWindow, App &aApp);
            static void buildConnectedPlayersAndEggs(Ogre::SceneManager *aSceneManager, const ServerData &aServerData);
    };
} // namespace Zappy::GUI

#endif /* !SCENEBUILDER_HPP_ */
