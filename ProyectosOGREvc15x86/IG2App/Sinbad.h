#pragma once

#include "Objetillos.h"
#include <OgreAnimationState.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

class Sinbad : public Objetillos
{
public:
	Sinbad(Ogre::SceneNode* mSinbad);
	~Sinbad();


	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void frameRendered(const Ogre::FrameEvent& evt);

protected:
	Ogre::SceneNode* mSinbadNode;
	Ogre::AnimationState* animationState = nullptr;
	Ogre::AnimationState* dance = nullptr;
	Ogre::AnimationState* runBase = nullptr;
	Ogre::AnimationState* runTop = nullptr;
	Ogre::Animation* animation = nullptr;
	Ogre::Vector3 keyframePos;
	bool dancing = false;
};

