#include "CameraController.h"


#include <OGRE/Bites/OgreApplicationContext.h>
#include <OgreColourValue.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OGRE/OgreMath.h>


#include "Ogre3DApplication.h"


CameraController::CameraController()
{
	scnMgr = nullptr;
	camNode = nullptr;
	viewPort = nullptr;
	scnMgr = nullptr;
}


CameraController::~CameraController()
{
	delete camNode;
	delete camera;
	delete viewPort;
	delete scnMgr;

	
}


CameraController::CameraController(Ogre::SceneManager & scnMgrRef, Ogre3DApplication& parent)
{
	// Store the reference to the scene manager.
	scnMgr = &scnMgrRef;

	// Create a node for the cam and translate it to the initial xyz.
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->translate(INITIAL_CAM_X, INITIAL_CAM_Y, INITIAL_CAM_Z);
	camNode->lookAt(Ogre::Vector3(0, -1, 0), Ogre::Node::TS_LOCAL);

	// Create the camera and set its default clipping, aspect ratio and attach to the camNode.
	camera = scnMgr->createCamera("MainCam");
	camera->setNearClipDistance(5);
	camera->setAutoAspectRatio(true);
	camNode->attachObject(camera);

	// Create a viewport using the parent Ogre3DApp.
	viewPort = parent.getRenderWindow()->addViewport(camera);
	viewPort->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	camera->setAspectRatio(getAspectRatio());
}

void CameraController::Zoom(int value)
{
	Ogre::Vector3 resultant = Ogre::Vector3(1140, 0, 950) - camNode->getPosition();
	resultant.normalise();

	camNode->translate(resultant * value * SCROLL_SPEED_MULTIPLIER);

	if (camNode->getPosition().y < 100)
	{
		camNode->setPosition(camNode->getPosition().x, 100, camNode->getPosition().z);
	}
	else if (camNode->getPosition().y > 4000)
	{
		camNode->setPosition(camNode->getPosition().x, 4000, camNode->getPosition().z);
	}
}

Ogre::Vector3 CameraController::GetDirection() const
{
	return camera->getDerivedDirection();
}

void CameraController::GetCameraToViewportRay(Ogre::Real x, Ogre::Real y, Ogre::Ray * out) const
{
	camera->getCameraToViewportRay(x, y, out);
}


//getAspectRatio()
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		getAspectRatio(Ogre::Viewport* vp)

Summary:	Gets an Ogre::Real value representing the aspect ratio of the passed in viewport.

Args:		vp
				the viewport to calculate the aspect ratio for.

Returns:	Ogre::Real value representing the viewport vp's width/height
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Ogre::Real CameraController::getAspectRatio()
{
	//Return an Ogre::Real number representing the width/height of the viewport.
	return Ogre::Real(Ogre::Real(viewPort->getActualWidth()) / Ogre::Real(viewPort->getActualHeight()));
}

