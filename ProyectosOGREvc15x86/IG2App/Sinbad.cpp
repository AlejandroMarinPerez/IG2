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
	sword4 = mSinbadNode->getCreator()->createEntity("Sword.mesh");

	ent->attachObjectToBone("Handle.R", sword1);
	ent->attachObjectToBone("Sheath.L", sword2);
	ent->attachObjectToBone("Sheath.R", sword3);
	ent->attachObjectToBone("Handle.L", sword4);
	mSinbadNode->attachObject(ent);

	//mSinbadNode->setPosition(400, 100, -300);
	mSinbadNode->setScale(20, 20, 20);
	mSinbadNode->setInitialState();
	sword3->setVisible(dancing);
	sword1->setVisible(!dancing);
	sword4->setVisible(false);
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

	temp = bombPos - temp;

	return temp;
}

void Sinbad::creaAnimacionBomba()
{
	if (!haBombeado) {
		//Atributos
		int duracionBomb = 12;
		int caida = 2;
		Ogre::Real longitudPasoBomb = duracionBomb / 5.0;
		Ogre::Real longitudPasoBomb2 = 1000;
		Ogre::Vector3 src(0, 0, 1);
		int longitud = 300;
		int longitudInf = 1000000;
		Ogre::TransformKeyFrame * kf2;
		Ogre::Vector3 temp;
		Ogre::Quaternion orRot;

		//Funcion
		//---------------------------------------------------------------------------
		//Animacion movimiento hacia la Bomba-----------------------------------------
		//---------------------------------------------------------------------------

		animationBomb = mSinbadNode->getCreator()->createAnimation("anMovBombSinbad", duracionBomb);
		Ogre::NodeAnimationTrack* track2 = animationBomb->createNodeTrack(0);
		orRot = mSinbadNode->getOrientation();

		keyframePos = mSinbadNode->getPosition();

		track2->setAssociatedNode(mSinbadNode);

		//Posicion 0
		kf2 = track2->createNodeKeyFrame(longitudPasoBomb * 0);
		kf2->setTranslate(keyframePos);
		kf2->setRotation(orRot);
		runBase->setEnabled(true);
		runTop->setEnabled(true);

		//Posicion 1
		temp = calculateDir();
		kf2 = track2->createNodeKeyFrame(longitudPasoBomb * 1);
		keyframePos += Ogre::Vector3::UNIT_Z;
		kf2->setTranslate(keyframePos);
		Ogre::Quaternion quat4 = src.getRotationTo(temp);
		kf2->setRotation(quat4);

		//Posicion 2
		temp.normalise();
		kf2 = track2->createNodeKeyFrame(longitudPasoBomb * 2);
		keyframePos += temp * longitud;
		deadPos = keyframePos;
		kf2->setTranslate(keyframePos);
		kf2->setRotation(quat4);

		//Posicion 3
		kf2 = track2->createNodeKeyFrame(caida * 3);
		keyframePos += Ogre::Vector3::UNIT_Z;
		keyframePos.y = 0;
		kf2->setTranslate(keyframePos);
		Ogre::Quaternion quat5 = src.getRotationTo(Ogre::Vector3(0, 1, 0));
		kf2->setRotation(quat5);


		//Posicion 4
		kf2 = track2->createNodeKeyFrame(longitudPasoBomb2 * 4);
		keyframePos += Ogre::Vector3::UNIT_X * longitudInf;
		kf2->setTranslate(keyframePos);
		kf2->setRotation(quat5);

		animationBomb->setInterpolationMode(Ogre::Animation::IM_LINEAR);

		animationBombState = mSinbadNode->getCreator()->createAnimationState("anMovBombSinbad");

		animationBombState->setLoop(false);
		animationBombState->setEnabled(true);

		//---------------------------------------------------------------------------
		//Animacion movimiento hacia la Bomba FIN------------------------------------
		//---------------------------------------------------------------------------

		haBombeado = true;
	}

	else 
		return;
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

		hanChocado();

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

	if (mSinbadNode->getPosition() == deadPos) {
		muerto();
	}
	
	if (mSinbadNode->getPosition() == orPos) {
		runBase->setEnabled(true);
		runTop->setEnabled(true);
	}
}
