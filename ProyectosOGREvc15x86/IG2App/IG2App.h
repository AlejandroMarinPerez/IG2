#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>
#include <OgreTexture.h>
#include <OgreRenderSystem.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>
#include <OgreRenderTarget.h>
#include <OgreRenderTargetListener.h>


class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;
  Ogre::SceneNode* mPlaneNode = nullptr;
  Ogre::SceneNode* mToyNode = nullptr;
  Ogre::SceneNode* mPanelNode = nullptr;

  OgreBites::CameraMan* mCamMgr = nullptr;
 
};

#endif
