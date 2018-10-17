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

	void frameRendered(const Ogre::FrameEvent& evt);

protected:
	Ogre::SceneNode* mSinbadNode;
	Ogre::AnimationState* animationState = nullptr;
	Ogre::Animation* animation = nullptr;
	Ogre::Vector3 keyframePos;
};

