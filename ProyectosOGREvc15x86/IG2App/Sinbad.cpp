#include "Sinbad.h"



Sinbad::Sinbad(Ogre::SceneNode* mSinbad, Ogre::Vector3 bomBPos)
{
	//Atributes
	mSinbadNode = mSinbad;
	int duracion = 20;
	int longitud = 600;
	int longitudX = 800;
	Ogre::Real longitudPaso = duracion / 8.0;
	Ogre::TransformKeyFrame * kf;
	keyframePos = Ogre::Vector3(0, 0, 0);
	Ogre::Vector3 src (0, 0, 1);
	Ogre::Vector3 dest (-1, 0, 0);
	Ogre::Quaternion quat;

	//Function
	bombPos = bomBPos;
	ent = mSinbadNode->getCreator()->createEntity("Sinbad.mesh");
	sword1 = mSinbadNode->getCreator()->createEntity("Sword.mesh");
	sword2 = mSinbadNode->getCreator()->createEntity("Sword.mesh");
	sword3 = mSinbadNode->getCreator()->createEntity("Sword.mesh");

	ent->attachObjectToBone("Handle.R", sword1);
	ent->attachObjectToBone("Sheath.L", sword2);
	ent->attachObjectToBone("Sheath.R", sword3);
	mSinbadNode->attachObject(ent);

	//mSinbadNode->setPosition(400, 100, -300);
	mSinbadNode->setScale(20, 20, 20);
	mSinbadNode->setInitialState();
	sword3->setVisible(dancing);
	sword1->setVisible(!dancing);
	bombPos.y = 100;
	
	//---------------------------------------------------------------------------
	//Animacion movimiento rodeando el plano-------------------------------------
	//---------------------------------------------------------------------------
	
	animation = mSinbad->getCreator()->createAnimation("anMov", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);

	keyframePos = Ogre::Vector3(400, 100, -300);

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
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * longitudX;
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
	keyframePos += Ogre::Vector3::UNIT_X * longitudX;
	kf->setTranslate(keyframePos);
	kf->setRotation(quat3);


	animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);

	animationState = mSinbadNode->getCreator()->createAnimationState("anMov");

	animationState->setLoop(true);
	animationState->setEnabled(true);

	//---------------------------------------------------------------------------
	//Animacion movimiento rodeando el plano FIN---------------------------------
	//---------------------------------------------------------------------------


	//---------------------------------------------------------------------------
	//Animaciones predeterminadas------------------------------------------------
	//---------------------------------------------------------------------------
	dance = ent->getAnimationState("Dance");

	dance->setLoop(true);
	dance->setEnabled(false);

	runBase = ent->getAnimationState("RunBase");

	runBase->setLoop(true);
	runBase->setEnabled(true);

	runTop = ent->getAnimationState("RunTop");

	runTop->setLoop(true);
	runTop->setEnabled(true);
	//---------------------------------------------------------------------------
	//Animaciones predeterminadas FIN--------------------------------------------
	//---------------------------------------------------------------------------
}


Sinbad::~Sinbad()
{
}

Ogre::Vector3 Sinbad::calculateDir()
{
	Ogre::Vector3 temp = mSinbadNode->getPosition();

	temp -= bombPos;

	return temp;
}

void Sinbad::creaAnimacionBomba()
{
	//Atributos
	int duracionBomb = 10;
	Ogre::Real longitudPasoBomb = duracionBomb / 4.0;
	Ogre::Vector3 src(0, 0, 1);
	int longitud = 300;
	Ogre::TransformKeyFrame * kf2;

	//Funcion
	//---------------------------------------------------------------------------
	//Animacion movimiento hacia la Bomba-----------------------------------------
	//---------------------------------------------------------------------------

	animationBomb = mSinbadNode->getCreator()->createAnimation("anMovBomb", duracionBomb);
	Ogre::NodeAnimationTrack* track2 = animationBomb->createNodeTrack(0);

	keyframePos = mSinbadNode->getPosition();

	track2->setAssociatedNode(mSinbadNode);

	//Posicion 0
	kf2 = track2->createNodeKeyFrame(longitudPasoBomb * 0);
	kf2->setTranslate(keyframePos);


	//Posicion 1
	kf2 = track2->createNodeKeyFrame(longitudPasoBomb * 1);
	keyframePos += Ogre::Vector3::UNIT_Z;
	kf2->setTranslate(keyframePos);
	Ogre::Quaternion quat4 = src.getRotationTo(calculateDir());
	kf2->setRotation(quat4);


	//Posicion 2
	kf2 = track2->createNodeKeyFrame(longitudPasoBomb * 2);
	keyframePos += calculateDir() * longitud;
	kf2->setTranslate(keyframePos);

	animationBomb->setInterpolationMode(Ogre::Animation::IM_LINEAR);

	animationBombState = mSinbadNode->getCreator()->createAnimationState("anMovBomb");

	animationBombState->setLoop(false);
	animationBombState->setEnabled(false);

	//---------------------------------------------------------------------------
	//Animacion movimiento hacia la Bomba FIN------------------------------------
	//---------------------------------------------------------------------------
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{

	switch (evt.keysym.sym) {
	case SDLK_r:

		dancing = !dancing;
		animationState->setEnabled(!dancing);
		dance->setEnabled(dancing);
		runBase->setEnabled(!dancing);
		runTop->setEnabled(!dancing);
		sword3->setVisible(dancing);
		sword1->setVisible(!dancing);
		
		return true;

	case SDLK_b:

		creaAnimacionBomba();

		animationState->setEnabled(false);
		dance->setEnabled(false);
		runBase->setEnabled(false);
		runTop->setEnabled(false);
		animationBombState->setEnabled(true);

		return true;


	}

	return false;
}

void Sinbad::frameRendered(const Ogre::FrameEvent & evt)
{
	if (animationState->getEnabled()) {
		animationState->addTime(evt.timeSinceLastFrame);
	}

	if (dance->getEnabled()) {
		dance->addTime(evt.timeSinceLastFrame);
	}

	if (runBase->getEnabled()) {
		runBase->addTime(evt.timeSinceLastFrame);
	}

	if (runTop->getEnabled()) {
		runTop->addTime(evt.timeSinceLastFrame);
	}

	if (animationBombState != nullptr) {
		if (animationBombState->getEnabled()) {
			animationBombState->addTime(evt.timeSinceLastFrame);
		}
	}
}
