//=====================================================
//			Filename: Ogre3DApplication.h
//=====================================================
#pragma once


//=====================================================
//					Forward Declarations.
//=====================================================
class CameraController;
class InputController;
class TileManager;
class Agent;
namespace Ogre {
	class SceneManager;
}


//=====================================================
//					Library Includes.
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
				Handles the setup of the screen and ogre rendering system.
			virtual bool frameRenderingQueued(FrameEvent &) override
				Handle the render queueing of frames.

			virtual bool keyPressed(const KeyboardEvent &evt) override
				Handles and processes user input.
			virtual bool mouseWheelRolled(MouseWheelEvent &) override
				Handles the scrolling of the mouseWheel.
			virtual bool mousePressed(MouseButtonEvent &) override
				Handles the pressing of any mousebutton.
			virtual bool mouseReleased(MouseButtonEvent &) override
				Handles the releasing of any mouseButton.
			virtual bool mouseMoved(MouseMotionEvent &) override
				Handles the movement of the mouse.
			virtual void frameRendered(FrameEvent &) override
				Handles what happens when a frame is rendered.

			virtual void buttonHit(Button *) override
				Handles the interaction of each button.

			====================== PRIVATE ====================
			void SetupResources()
				Loads all resources for use by the Ogre rendering system.

			void SetupUITray(String &, RenderWindow *)
				Sets up the initial default UI display.


Members:	==================== PRIVATE ====================
			CameraController* mCamControl
				the cameraController object to be used by the system.
			InputController* mInControl
				the input controller object to be used by the system.
			SceneManager* g_ScnMgr
				a reference to the global sceneManager singleton used by the 
				Ogre rendering system.
			TileManager* mTileMgr
				the tileManager object to be used by the system.
			Agent* mAgent
				the Agent to be controlled by the system/user.
			TrayManager* mTrayManager
				a reference to the Tray manager to be used by the ogre
				rendering system.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Ogre3DApplication : public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener
{
public:
	//Constructors and deconstructors.
	Ogre3DApplication();
	~Ogre3DApplication();

	//Overriden methods from OgreBits::ApplicationContext:
	virtual void setup() override;
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

	//Overriden methods from OgreBits::InputListener:
	virtual bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
	virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent & evt) override;
	virtual bool mousePressed(const OgreBites::MouseButtonEvent & evt) override;
	virtual bool mouseReleased(const OgreBites::MouseButtonEvent& evt) override;
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	// Overriden methods from OgreBites::TrayListener.
	virtual void buttonHit(OgreBites::Button* button) override;

private:
	void SetupResources();

	void setupUITray(Ogre::RenderWindow * window);

private:
	CameraController* mCamControl;

	InputController* mInControl;

	Ogre::SceneManager* g_ScnMgr;

	TileManager* mTileMgr;

	Agent* mAgent;

	OgreBites::TrayManager* mTrayManager;

};