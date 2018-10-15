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
		mPlaneNode->getCreator()->setAmbientLight(Ogre::ColourValue::White);
		//mPlaneNode->getAttachedObject("nPlane")->setVisible(false);
		mPlaneNode->getAttachedObjects()[0]->setVisible(false);
	};

	void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) {
		mPlaneNode->getCreator()->setAmbientLight(Ogre::ColourValue::White);
		//mPlaneNode->getAttachedObject("nPlane")->setVisible(true);
		mPlaneNode->getAttachedObjects()[0]->setVisible(true);
	};

protected: 
	Ogre::SceneNode* mPlaneNode;
};

