//=====================================================
//					Filename: CameraController.cpp
//=====================================================


//=====================================================
//				Source Includes.
//=====================================================
#include "CameraController.h"
#include "Ogre3DApplication.h"


//=====================================================
//				Library Includes.
//=====================================================
#include <OGRE/Bites/OgreApplicationContext.h>
#include <OgreColourValue.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OGRE/OgreMath.h>
#include <OGRE/Bites/OgreTrays.h>


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		CameraController

Summary:	The Default constructor for a CameraController.

Modifies:	[ALL MEMBER VARIABLES]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
CameraController::CameraController()
{
	g_ScnMgr = nullptr;
	mCamNode = NULL;
	mViewPort = NULL;
	mCamera = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		~CameraController

Summary:	The Default deconstructor for a CameraController.

Modifies:	[ALL MEMBER VARIABLES]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
CameraController::~CameraController()
{
	if(mCamNode)
		delete mCamNode;
	if(mCamera)
		delete mCamera;
	if(mViewPort)
		delete mViewPort;
	if(g_ScnMgr)
		delete g_ScnMgr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		CameraController

Summary:	The Preferred constructor for a CameraController.

Args:		SceneManager *& scnMgrRef
				A pointer reference to the SceneManager to use to set
				this cameraController up.
			Ogre3DApplication *& parent
				A pointer reference to the Ogre3DApplication that this
				cameraController belongs to.

Modifies:	[ALL MEMBER VARIABLES]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
CameraController::CameraController(Ogre::SceneManager *& scnMgrRef, Ogre3DApplication *& parent)
{
	// Store the reference to the scene manager.
	g_ScnMgr = scnMgrRef;

	// Create a node for the cam and translate it to the initial xyz.
	mCamNode = g_ScnMgr->getRootSceneNode()->createChildSceneNode();
	mCamNode->translate(INITIAL_CAM_X, INITIAL_CAM_Y, INITIAL_CAM_Z);
	mCamNode->lookAt(Ogre::Vector3(0, -1, 0), Ogre::Node::TS_LOCAL);

	// Create the mCamera and set its default clipping, aspect ratio and attach to the mCamNode.
	mCamera = g_ScnMgr->createCamera("MainCam");
	mCamera->setNearClipDistance(5);
	mCamera->setAutoAspectRatio(true);
	mCamNode->attachObject(mCamera);

	// Create a viewport using the parent Ogre3DApp.
	mViewPort = parent->getRenderWindow()->addViewport(mCamera);
	mViewPort->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	mCamera->setAspectRatio(getAspectRatio());
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		Zoom

Summary:	Zooms the camera in and out based on value.

Args:		int value
				the y value to zoom the camera by.

Modifies:	[mCamNode]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void CameraController::Zoom(int value)
{
	// Calculate the direction vector for scrolling.
	Ogre::Vector3 resultant = Ogre::Vector3(1140, 0, 950) - mCamNode->getPosition();
	resultant.normalise();

	// Translate the camNode by the direction vector, the value, and the scroll speed multiplier.
	mCamNode->translate(resultant * value * SCROLL_SPEED_MULTIPLIER);

	// Perfom bounds checking for the camera's y value.
	if (mCamNode->getPosition().y < 100)
	{
		mCamNode->setPosition(mCamNode->getPosition().x, 100, mCamNode->getPosition().z);
	}
	else if (mCamNode->getPosition().y > 4000)
	{
		mCamNode->setPosition(mCamNode->getPosition().x, 4000, mCamNode->getPosition().z);
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		GetDirection

Summary:	Get the direction vector of the camera.

Returns:	Vector3
				a vector representing the Direction of the camera held
				by this cameraController.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Ogre::Vector3 CameraController::GetDirection() const
{
	return mCamera->getDerivedDirection();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		GetCameraToViewportRay

Summary:	Get a Ray into the screen at the mouse co-ords on the screen
			in world space.

Args:		Real x
				the x co-ords of the mouse on the screen.
			Real y
				the y co-ords of the mouse on the screen.
			Ray * out
				A pointer to store the resultant ray at.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void CameraController::GetCameraToViewportRay(Ogre::Real x, Ogre::Real y, Ogre::Ray * out) const
{
	//Calculate the co-ords in 0.0-1.0 terms.
	const Ogre::Vector2 pt(x / mViewPort->getActualWidth(), y / mViewPort->getActualHeight());

	// Calculate and store the ray.
	*out = OgreBites::TrayManager::screenToScene(mCamera, pt);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		getAspectRatio()

Summary:	Gets an Ogre::Real value representing the aspect ratio of the passed in viewport.

Returns:	Ogre::Real value representing the viewport vp's width/height
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Ogre::Real CameraController::getAspectRatio()
{
	//Return an Ogre::Real number representing the width/height of the viewport.
	return Ogre::Real(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));
}

