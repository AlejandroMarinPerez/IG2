#include "Plano.h"



Plano::Plano(Ogre::SceneNode* plano)
{
	mPlaneNode = plano;

	Ogre::Entity* plane = plano->getCreator()->createEntity("mPlane1080x800.mesh");

	mPlaneNode->attachObject(plane);

	plane->setMaterialName("IG2App/PlaneMaterial");

}


Plano::~Plano()
{
}
