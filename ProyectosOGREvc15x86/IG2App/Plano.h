#pragma once

#include "Objetillos.h"
#include <OgreRenderTargetListener.h>

class Plano : public Objetillos, public Ogre::RenderTargetListener
{
public:
	//CLASE DEL PLANO
	Plano(Ogre::SceneNode* plano);
	~Plano();

	void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) {
		mPlaneNode->getAttachedObjects()[0]->setVisible(false);
		mPlaneNode->getCreator()->setAmbientLight(Ogre::ColourValue(0.10, 0.10, 0.25, 0.10));
		//mPlaneNode->getAttachedObject("nPlane")->setVisible(false);
	};

	void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) {
		mPlaneNode->getAttachedObjects()[0]->setVisible(true);
		mPlaneNode->getCreator()->setAmbientLight(Ogre::ColourValue::ZERO);
		//mPlaneNode->getAttachedObject("nPlane")->setVisible(true);
	};

	Ogre::Entity* getEntityPlane() {
		return planeEnt;
	}

protected: 
	Ogre::SceneNode* mPlaneNode;
	Ogre::Entity* planeEnt = nullptr;
};

