/*
** EPITECH PROJECT, 2023
** zap
** File description:
** EntityFactory
*/

#ifndef ENTITYFACTORY_HPP_
#define ENTITYFACTORY_HPP_

#include <OgrePrerequisites.h>
#include "EggData.hpp"
#include "PlayerData.hpp"

namespace Ogre {
    class SceneManager;
    class RenderWindow;
} // namespace Ogre

namespace Zappy::GUI {
    class ElementFactory
    {
        public:
            ElementFactory() = delete;
            ~ElementFactory() = delete;

            static void createTile(Ogre::SceneManager *aSceneManager, const Ogre::Vector2 &aPosition,
                                   const std::string &aName);

            static void createPlayer(Ogre::SceneManager *aSceneManager, const PlayerData &aPlayerData);

            static void createEgg(Ogre::SceneManager *aSceneManager, const EggData &aEggData);

            static std::pair<float, float> createText(const std::string &aOverlayName, const std::string &aText,
                                                      const std::string &aPrefix, const Ogre::Vector2 &aPosition,
                                                      const std::string &aMaterialName = "BaseWhite");

        private:
            static std::pair<float, float> calculateDimensions(const std::string &aButtonText);
    };
} // namespace Zappy::GUI

#endif /* !ENTITYFACTORY_HPP_ */
