#include "Bomb.h"



Bomb::Bomb(Ogre::SceneNode* bombNode)
{
	//Atributes
	int duracion = 16;
	int longitud = 25;
	Ogre::Real longitudPaso = duracion / 4.0;
	Ogre::TransformKeyFrame * kf;

	//FUnctions
	mBombNode = bombNode;

	Ogre::Entity* bomb = bombNode->getCreator()->createEntity("uv_sphere.mesh");

	mBombNode->attachObject(bomb);
	mBombNode->setScale(0.5, 0.5, 0.5);
	mBombNode->setPosition(0, 0, 0);
	mBombNode->setInitialState();

	bomb->setMaterialName("IG2App/Bomb");

	animation = bombNode->getCreator()->createAnimation("anVaiven", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);

	keyframePos = Ogre::Vector3(0, 0, 0);

	track->setAssociatedNode(mBombNode);

	//Posicion 0
	kf = track->createNodeKeyFrame(longitudPaso * 0);
	kf->setTranslate(keyframePos);

	//Posicion 1
	kf = track->createNodeKeyFrame(longitudPaso * 1);
	keyframePos += Ogre::Vector3::UNIT_Y * longitud;
	kf->setTranslate(keyframePos);

	//Posicion 2
	kf = track->createNodeKeyFrame(longitudPaso * 2);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longitud;
	kf->setTranslate(keyframePos);

	//Posicion 3
	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longitud;
	kf->setTranslate(keyframePos);

	//Posicion 4
	kf = track->createNodeKeyFrame(longitudPaso * 4);
	keyframePos += Ogre::Vector3::UNIT_Y * longitud;
	kf->setTranslate(keyframePos);

	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);

	animationState = bombNode->getCreator()->createAnimationState("anVaiven");

	animationState->setLoop(true);
	animationState->setEnabled(true);
}


Bomb::~Bomb()
{
}

void Bomb::frameRendered(const Ogre::FrameEvent & evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}
