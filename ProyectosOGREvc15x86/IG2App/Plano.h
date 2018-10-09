#pragma once

#include "Objetillos.h"

class Plano
{
public:
	//CLASE DEL PLANOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	Plano(Ogre::SceneNode* plano);
	~Plano();

protected: 
	Ogre::SceneNode* mPlaneNode;
};

