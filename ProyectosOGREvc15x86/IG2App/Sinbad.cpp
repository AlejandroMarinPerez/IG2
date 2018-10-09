#include "Sinbad.h"



Sinbad::Sinbad(Ogre::SceneNode* mSinbad)
{
	mSinbadNode = mSinbad;

	Ogre::Entity* ent = mSinbadNode->getCreator()->createEntity("Sinbad.mesh");
	mSinbadNode->attachObject(ent);

	mSinbadNode->setPosition(400, 100, -300);
	mSinbadNode->setScale(20, 20, 20);

}


Sinbad::~Sinbad()
{
}
