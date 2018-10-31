#include "Toy.h"



Toy::Toy(Ogre::SceneNode* mToy)
{
	Ogre::Real size = 0.5;
		
		mBB8 = mToy;

		mBB8->setPosition(100, size*100, 0);

		//Cuerpo
		Ogre::Entity* entCuer = mBB8->getCreator()->createEntity("sphere.mesh");
		mCuerpo = mBB8->createChildSceneNode("nCuerpo");
		mCuerpo->attachObject(entCuer);

		mCuerpo->setScale(size, size, size);


		//Ombligo
		Ogre::Entity* entOmbl = mBB8->getCreator()->createEntity("sphere.mesh");
		mOmbligo = mCuerpo->createChildSceneNode("nOmbl");
		mOmbligo->attachObject(entOmbl);

		mOmbligo->setScale(size / 5, size / 5, size / 5);
		mOmbligo->setPosition(0, 0, 100);

		//Cuello
		/*Ogre::Entity* entCuel = mBB8->getCreator()->createEntity("sphere.mesh");
		mCuello = mBB8->createChildSceneNode("nCuello");
		mCuello->attachObject(entCuel);

		mCuello->setScale(0.1, 0.1, 0.1);
		mCuello->setPosition(0, 93, 0);*/

		//Cabeza
		Ogre::Entity* entCab = mBB8->getCreator()->createEntity("sphere.mesh");
		mCabesa = mBB8->createChildSceneNode("nCabesa");
		mCabesa->attachObject(entCab);

		mCabesa->setScale(size / 2, size / 2, size / 2);
		mCabesa->setPosition(0, size*150, 0);

		//Nariz
		Ogre::Entity* entNar = mBB8->getCreator()->createEntity("sphere.mesh");
		mNariz = mCabesa->createChildSceneNode("nNariz");
		mNariz->attachObject(entNar);

		mNariz->setScale(size / 3.3, size / 3.3, size / 3.3);
		mNariz->setPosition(0, 0, 100);
}


Toy::~Toy()
{
}

bool Toy::keyPressed(const OgreBites::KeyboardEvent & evt)
{

	switch (evt.keysym.sym) {
	case SDLK_t:

		ToyMovement();

		return true;

	case SDLK_y:

		moves = !moves;

		return true;

	case SDLK_v:

		mBB8->yaw(Ogre::Degree(45));
		//mBB8->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(45), Ogre::Node::TS_LOCAL);
		//mBB8->setOrientation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3(0, 1, 0)));

		return true;

	}

	return false;

}

void Toy::frameRendered(const Ogre::FrameEvent & evt)
{
	if (moves) {
		mCabesa->yaw(Ogre::Degree(1.0));
		mCuerpo->pitch(Ogre::Degree(1.0));
		Ogre::Vector3 pos = mBB8->getPosition();
		mBB8->translate(0, 0, 1 + evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	}
}

void Toy::ToyMovement()
{
	mCabesa->yaw(Ogre::Degree(1.0));
	mCuerpo->pitch(Ogre::Degree(1.0));
	Ogre::Vector3 pos = mBB8->getPosition();
	mBB8->translate( 0, 0, 1, Ogre::Node::TS_LOCAL);
}
