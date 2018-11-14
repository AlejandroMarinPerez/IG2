#pragma once

#include "Objetillos.h"

class Toy : public Objetillos
{
public:
	Toy(Ogre::SceneNode* mToy);
	~Toy();

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void frameRendered(const Ogre::FrameEvent& evt);

	Ogre::SceneNode* getCuerpo() {
		return mCuerpo;
	}

	void haChocado() {
		mCuerpo->getAttachedObjects()[0]->setVisible(false);
		mCabesa->getAttachedObjects()[0]->setVisible(false);
		mNariz->getAttachedObjects()[0]->setVisible(false);
		mOmbligo->getAttachedObjects()[0]->setVisible(false);
		isActivo = false;
	}

protected:
	bool moves = false;
	Ogre::SceneNode* mBB8 = nullptr;
	Ogre::SceneNode* mCuerpo = nullptr;
	Ogre::SceneNode* mCabesa = nullptr;
	Ogre::SceneNode* mCuello = nullptr;
	Ogre::SceneNode* mNariz = nullptr;
	Ogre::SceneNode* mOmbligo = nullptr;
	bool isActivo = true;

	void ToyMovement();
};

