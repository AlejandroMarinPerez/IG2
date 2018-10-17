#include "Sinbad.h"



Sinbad::Sinbad(Ogre::SceneNode* mSinbad)
{
	//Atributes
	mSinbadNode = mSinbad;
	int duracion = 16;
	int longitud = 600;
	//int longitudX = 800;
	Ogre::Real longitudPaso = duracion / 8.0;
	Ogre::TransformKeyFrame * kf;
	keyframePos = Ogre::Vector3(0, 0, 0);
	Ogre::Vector3 src (0, 0, 1);
	Ogre::Vector3 dest (-1, 0, 0);
	Ogre::Quaternion quat;

	//Function
	Ogre::Entity* ent = mSinbadNode->getCreator()->createEntity("Sinbad.mesh");
	mSinbadNode->attachObject(ent);

	mSinbadNode->setPosition(400, 100, -300);
	mSinbadNode->setScale(20, 20, 20);
	mSinbadNode->setInitialState();
	
	animation = mSinbad->getCreator()->createAnimation("anMov", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);

	keyframePos = Ogre::Vector3(0, 0, 0);

	track->setAssociatedNode(mSinbadNode);

	//Posicion 0
	kf = track->createNodeKeyFrame(longitudPaso * 0);
	kf->setTranslate(keyframePos);

	//Posicion 1
	kf = track->createNodeKeyFrame(longitudPaso * 1);
	keyframePos += Ogre::Vector3::UNIT_Z * longitud;
	kf->setTranslate(keyframePos);

	//Posicion 2
	kf = track->createNodeKeyFrame(longitudPaso * 2);
	keyframePos += Ogre::Vector3::UNIT_Z;
	kf->setTranslate(keyframePos);
	quat = src.getRotationTo(dest);
	kf->setRotation(quat);

	//Posicion 3
	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * longitud;
	kf->setTranslate(keyframePos);
	kf->setRotation(quat);

	//Posicion 4
	Ogre::Vector3 dest2(0, 0, -1);
	kf = track->createNodeKeyFrame(longitudPaso * 4);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X;
	kf->setTranslate(keyframePos);
	Ogre::Quaternion quat2 = src.getRotationTo(dest2);
	kf->setRotation(quat2);

	//Posicion 5
	kf = track->createNodeKeyFrame(longitudPaso * 5);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Z * longitud;
	kf->setTranslate(keyframePos);
	kf->setRotation(quat2);

	//Posicion 6
	Ogre::Vector3 dest3(1, 0, 0);
	kf = track->createNodeKeyFrame(longitudPaso * 6); 
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Z;
	kf->setTranslate(keyframePos);
	Ogre::Quaternion quat3 = src.getRotationTo(dest3);
	kf->setRotation(quat3);

	//Posicion 7
	kf = track->createNodeKeyFrame(longitudPaso * 7);
	keyframePos += Ogre::Vector3::UNIT_X * longitud;
	kf->setTranslate(keyframePos);
	kf->setRotation(quat3);


	animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);

	animationState = mSinbadNode->getCreator()->createAnimationState("anMov");

	animationState->setLoop(true);
	animationState->setEnabled(true);

}


Sinbad::~Sinbad()
{
}

void Sinbad::frameRendered(const Ogre::FrameEvent & evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}
