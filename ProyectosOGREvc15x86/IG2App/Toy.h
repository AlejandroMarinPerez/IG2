#pragma once

#include "Objetillos.h"

class Toy : public Objetillos
{
public:
	Toy(Ogre::SceneNode* mToy);
	~Toy();

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void frameRendered(const Ogre::FrameEvent& evt);

protected:
	bool moves = false;
	Ogre::SceneNode* mBB8 = nullptr;
	Ogre::SceneNode* mCuerpo = nullptr;
	Ogre::SceneNode* mCabesa = nullptr;
	Ogre::SceneNode* mCuello = nullptr;
	Ogre::SceneNode* mNariz = nullptr;
	Ogre::SceneNode* mOmbligo = nullptr;

	void ToyMovement();
};

