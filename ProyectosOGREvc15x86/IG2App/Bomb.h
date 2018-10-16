#pragma once

#include "Objetillos.h"
#include <OgreAnimationState.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

class Bomb : public Objetillos
{
public:
	Bomb(Ogre::SceneNode* bombNode);
	~Bomb();

	void frameRendered(const Ogre::FrameEvent& evt);

protected:
	Ogre::SceneNode* mBombNode = nullptr;
	Ogre::AnimationState* animationState = nullptr;
	Ogre::Animation* animation = nullptr;
	Ogre::Vector3 keyframePos;
};

