//=====================================================
//			Filename: Ogre3DApplication.h
//=====================================================
#pragma once


class CameraController;
class InputController;
namespace Ogre {
	class SceneManager;
}

//=====================================================
//					Libraries
//=====================================================
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <Bites/OgreApplicationContext.h>
#include <Bites/OgreTrays.h>
#include <OgreViewport.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Ogre3DApplication

  Summary:  A Class to control the entire Ogre3D Application as of present.

  Methods:  ====================== PUBLIC ======================
			Ogre3DApplication()
				Default constructor for the Ogre3DApplication.
			~Ogre3DApplication()
				Default deconstructor for the Ogre3DApplication.

			virtual void setup() override
				From OgreBites::ApplicationContext
				Handles the setup of the screen and ogre rendering system.

			virtual bool keyPressed(const KeyboardEvent &evt)
				From OgreBites::InputListener.
				Handles and processes user input.

			====================== PRIVATE ====================
			Ogre::Real getAspectRatio(Ogre::Viewport* vp)
				Returns the aspect ration of the current screen.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Ogre3DApplication : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	//Constructors and deconstructors.
	Ogre3DApplication();
	~Ogre3DApplication();

	//Overriden methods from OgreBits::ApplicationContext:
	virtual void setup() override;

	//Overriden methods from OgreBits::InputListener:
	virtual bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
	virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent & evt) override;
	virtual bool mousePressed(const OgreBites::MouseButtonEvent & evt) override;


private:
	//Class methods.
	

	void SetupResources();

private:
	CameraController* camControl;

	InputController* inControl;

	Ogre::SceneManager* scnMgr;

};