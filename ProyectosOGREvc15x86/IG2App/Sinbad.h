#pragma once

#include "Objetillos.h"
#include <OgreAnimationState.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

class Sinbad : public Objetillos
{
public:
	Sinbad(Ogre::SceneNode* mSinbad, Ogre::Vector3 bomBPos);
	~Sinbad();
	Ogre::Vector3 calculateDir();
	void creaAnimacionBomba();

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void frameRendered(const Ogre::FrameEvent& evt);

protected:
	Ogre::SceneNode* mSinbadNode;
	Ogre::AnimationState* animationState = nullptr;
	Ogre::AnimationState* dance = nullptr;
	Ogre::AnimationState* runBase = nullptr;
	Ogre::AnimationState* runTop = nullptr;
	Ogre::AnimationState* animationBombState = nullptr;
	Ogre::Animation* animation = nullptr;
	Ogre::Animation* animationBomb = nullptr;
	Ogre::Vector3 keyframePos;
	Ogre::Vector3 bombPos;
	Ogre::Entity* ent = nullptr;
	Ogre::Entity* sword1 = nullptr;
	Ogre::Entity* sword2 = nullptr;
	Ogre::Entity* sword3 = nullptr;
	bool dancing = false;
};

