#pragma once

#include "Objetillos.h"

class Sinbad : public Objetillos
{
public:
	Sinbad(Ogre::SceneNode* mSinbad);
	~Sinbad();

protected:
	Ogre::SceneNode* mSinbadNode;
};

