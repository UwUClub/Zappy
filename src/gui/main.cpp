//
// Created by beafowl on 22/05/23.
//

#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/Ogre.h>
#include <OGRE/OgreSceneManager.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "ClientApi.hpp"
#include "ParserData.hpp"

int main()
{
    // open a window with a title
    OgreBites::ApplicationContext ctx("Zappy");
    ctx.initApp();
}
