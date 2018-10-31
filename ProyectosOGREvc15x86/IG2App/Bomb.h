#pragma once

#include "Objetillos.h"
#include <OgreAnimationState.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreParticleSystem.h>

class Bomb : public Objetillos
{
public:
	Bomb(Ogre::SceneNode* bombNode, Ogre::ParticleSystem* pSysOr);
	~Bomb();

	void frameRendered(const Ogre::FrameEvent& evt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void haChocado() {
		pSys->setEmitting(true);
	}

protected:
	Ogre::SceneNode* mBombNode = nullptr;
	Ogre::AnimationState* animationState = nullptr;
	Ogre::Animation* animation = nullptr;
	Ogre::Vector3 keyframePos;
	Ogre::ParticleSystem* pSys = nullptr;
};

