#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include "Plano.h"
#include "Sinbad.h"
#include "Bomb.h"
#include "Toy.h"

using namespace Ogre;

Bomb* bomba = nullptr;
Toy* toy = nullptr;
Sinbad* sinbad = nullptr;


bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_p) {
	  mPlaneNode->pitch(Ogre::Degree(1.0));
  }
  else if (evt.keysym.sym == SDLK_c) {
	  camOgre = !camOgre;
	  if (camOgre) {
		  mCamMgr->setTarget(mSinbadNode);
		  mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);
	  }
	  else {
		  mCamNode->setPosition(0, 0, 1000);
		  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
		  mCamMgr->setTarget(mSM->getRootSceneNode());
	  }
  }
  
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{

	
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1); 
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	Camera* camRef = mSM->createCamera("RefCam");
	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(10000);
	camRef->setAutoAspectRatio(true);



	//Añadimos la cámara del reflejo al nodo
	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);
	mCamNode->attachObject(camRef);


	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	
	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	//vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

	CompositorManager::getSingleton().addCompositor(vp, "Luminance");
	CompositorManager::getSingleton().setCompositorEnabled(vp, "Luminance", true);

	//Creamos la cámara del reflejo
  

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);



  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  //mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //mLightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  //PLANO y REFLEJO///////////////////////////////////////

  MeshManager::getSingleton().createPlane("mPlane1080x800.mesh", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::NEGATIVE_UNIT_Z);

  mPlaneNode = mSM->getRootSceneNode()->createChildSceneNode("nPlane");
  Plano* plane = new Plano(mPlaneNode);
  
  //Reflejo del plano 

  /*Entity* ent = mSM->createEntity("mPlane1080x800.mesh");
  mPlaneNode = mSM->getRootSceneNode()->createChildSceneNode("nPanel");
  mPlaneNode->attachObject(ent);*/

  plane->getEntityPlane()->setMaterialName("IG2App/PlaneMaterial");
  plane->getEntityPlane()->getSubEntities()[0]->getMaterial()->getTechniques()[0]->getPasses()[0]->createTextureUnitState("TexturaPlano2.jpg");

  //Añadimos la cámara y demás/////////////////////////////////
  MovablePlane* mp = new MovablePlane(Vector3::UNIT_Y, 0);
  mPlaneNode->attachObject(mp);

  camRef->enableReflection(mp);
  camRef->enableCustomNearClipPlane(mp);
  //////////////////////////////////////////////////////////////

  //Textura para el reflejo (Parte 3)/////////////////////////
  TexturePtr rttTex = TextureManager::getSingleton().createManual("texRtt", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, (Real)mWindow.render->getViewport(0)->getActualWidth(),
	  (Real)cam->getViewport()->getActualHeight(), 0, PF_R8G8B8, TU_RENDERTARGET);

  //Añadimos la cámara del reflejo como viewport
  RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
  Viewport* vpt = renderTexture->addViewport(camRef);

  vpt->setClearEveryFrame(true);
  vpt->setBackgroundColour(ColourValue::Black); 
  /////////////////////////////////////////////////////////////


  //4, añadir la unidad de textura al panel///////////////////
  TextureUnitState* tu = plane->getEntityPlane()->getSubEntities()[0]->getMaterial()->getTechniques()[0]->getPasses()[0]->createTextureUnitState("texRtt");

  tu->setColourOperation(LBO_ADD);
  tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
  tu->setProjectiveTexturing(true, camRef);
  //////////////////////////////////////////////////////////////

  renderTexture->addListener(plane);

  //------------------------------------------------------------------------


  //BOMB

  pSys = mSM->createParticleSystem("parSys", "Smoke");

  mBombNode = mSM->getRootSceneNode()->createChildSceneNode("nBomb");
  bomba = new Bomb(mBombNode, pSys);
  addInputListener(bomba);

  //------------------------------------------------------------------------

  //OGRO

  Ogre::Vector3 bombPos = mBombNode->getPosition();
  //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
  mSinbadNode = mPlaneNode->createChildSceneNode("nSinbad");
  sinbad = new Sinbad(mSinbadNode, bombPos);
  addInputListener(sinbad);
  
  
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);

  //------------------------------------------------------------------------

  //TOY

  mToyNode = mPlaneNode->createChildSceneNode("nToy");
  toy = new Toy(mToyNode);
  addInputListener(toy);

  //------------------------------------------------------------------------


  //------------------------------------------------------------------------

  //SKYPLANE
  //MeshManager::getSingleton().createPlane("mPlane1080x800.mesh", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::NEGATIVE_UNIT_Z);

  mSkyPlaneNode = mSM->getRootSceneNode()->createChildSceneNode("nSkyPlane");

  mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -20), "IG2App/mandelbrot1", 1, 1, true, 1, 100, 100); // , ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  //------------------------------------------------------------------------

  //Esto mueve la cámara. Hace que se gire con el ratón

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  

  //------------------------------------------------------------------------

 

}

void IG2App::frameRendered(const Ogre::FrameEvent & evt)
{
	toySphere = toy->getCuerpo()->getAttachedObjects()[0]->getWorldBoundingSphere();
	bombSphere = mBombNode->getAttachedObjects()[0]->getWorldBoundingSphere();


	if (bomba != nullptr && toy != nullptr && toySphere.intersects(bombSphere)) {
		bomba->haChocado();
		toy->haChocado();
		sinbad->hanChocado();
	}
}

