/*
** EPITECH PROJECT, 2023
** zap
** File description:
** SceneBuilder
*/

#ifndef SCENEBUILDER_HPP_
#define SCENEBUILDER_HPP_

#include <OGRE/Ogre.h>
#include <OgrePrerequisites.h>

namespace Ogre {
    class SceneManager;
    class RenderWindow;
} // namespace Ogre

namespace Zappy::GUI {
    struct ServerData;
    class PlayerData;
    struct EggData;
    class CameraHandler;
    class ClickHandler;
    class AnimationHandler;
    class App;

    using cameraReturn = std::pair<CameraHandler *, ClickHandler *>;

    /**
     * @brief Class used to build the scene
     * @details This class is used to build the scene, it contains only static methods
     */
    class SceneBuilder
    {
        public:
            SceneBuilder() = delete;
            ~SceneBuilder() = delete;

            SceneBuilder(const SceneBuilder &) = delete;
            SceneBuilder &operator=(const SceneBuilder &) = delete;
            SceneBuilder(SceneBuilder &&) = delete;
            SceneBuilder &operator=(SceneBuilder &&) = delete;

            /**
             * @brief Build the lights into the scene
             *
             * @param aSceneManager The scene manager to use
             * @param aCenter The center of the map
             */
            static void buildLights(Ogre::SceneManager *aSceneManager, const Ogre::Vector3 &aCenter);

            /**
             * @brief Build the map into the scene
             *
             * @param aSceneManager The scene manager to use
             * @param aServerData The server data of the game
             * @return Ogre::Vector3f The center of the map
             */
            static Ogre::Vector3f buildMap(Ogre::SceneManager *aSceneManager, const ServerData &aServerData);

            /**
             * @brief Build the camera into the scene
             *
             * @param aSceneManager The scene manager to use
             * @param aCenter The center of the map
             * @param aRenderWindow The render window to use
             * @param aApp The app to use
             * @return cameraReturn The camera handler and the click handler
             */
            static cameraReturn buildCamera(Ogre::SceneManager *aSceneManager, const Ogre::Vector3 &aCenter,
                                            Ogre::RenderWindow *aRenderWindow, App &aApp);

            /**
             * @brief Build the players and the eggs that are already on the map
             *
             * @param aSceneManager The scene manager to use
             * @param aServerData The server data of the game
             * @param aAnimatedEntities The animated entities
             */
            static void buildConnectedPlayersAndEggs(
                Ogre::SceneManager *aSceneManager, const ServerData &aServerData,
                std::unordered_map<Ogre::Entity *, std::unique_ptr<AnimationHandler>> &aAnimatedEntities);

            /**
             * @brief Create a Tile object
             *
             * @param aSceneManager The scene manager to use
             * @param aPosition The position of the tile
             * @param aName The name of the tile
             */
            static void createTile(Ogre::SceneManager *aSceneManager, const Ogre::Vector2 &aPosition,
                                   const std::string &aName);

            /**
             * @brief Create a Player object
             *
             * @param aSceneManager The scene manager to use
             * @param aPlayerData The player data representing the player to create
             * @param aAnimatedEntities The animated entities
             */
            static void
            createPlayer(Ogre::SceneManager *aSceneManager, const PlayerData &aPlayerData,
                         std::unordered_map<Ogre::Entity *, std::unique_ptr<AnimationHandler>> &aAnimatedEntities);

            /**
             * @brief Create a Egg object
             *
             * @param aSceneManager The scene manager to use
             * @param aEggData The egg data representing the egg to create
             */
            static void createEgg(Ogre::SceneManager *aSceneManager, const EggData &aEggData);

            /**
             * @brief Create a Text object
             *
             * @param aOverlayName The name of the overlay to use
             * @param aText The text to display
             * @param aPrefix The prefix to use (will be used to create the overlays elements, ex: "Time" will create
             * "Time_Panel" : overlayArea, "Time_Text" : TextArea)
             * @param aPosition The position of the text
             * @param aDimension The dimension of the background
             * @param aMaterialName The material to use if any
             */
            static void createText(const std::string &aOverlayName, const std::string &aText,
                                   const std::string &aPrefix, const Ogre::Vector2 &aPosition,
                                   const Ogre::Vector2 &aDimension, const std::string &aMaterialName = "BaseWhite",
                                   const std::string &aGroupName = "General",
                                   const Ogre::Vector2 &aOffset = Ogre::Vector2(10, 10));

            /**
             * @brief Set the Player Pos And Orientation object
             *
             * @param aPlayer the playerData
             * @param aSceneManager the scene manager
             */
            static void setPlayerPosAndOrientation(Ogre::SceneManager *aSceneManager, const PlayerData &aPlayer);

        private:
    };
} // namespace Zappy::GUI

#endif /* !SCENEBUILDER_HPP_ */
