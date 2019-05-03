//=====================================================
//				Filename: InputController.cpp
//=====================================================


//=====================================================
//				Source Includes.
//=====================================================
#include "InputController.h"
#include "RayCasting.h"
#include "CameraController.h"


//=====================================================
//					Library Includes.
//=====================================================
#include <OgreMath.h>
#include <OgreVector3.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreRay.h>


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		InputController

Summary:	The default constructor for an InputController.

Modifies:	[mRayCaster]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
InputController::InputController()
{
	mRayCaster = new RayCasting();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		~InputController

Summary:	The default deconstructor for an InputController.

Modifies:	[mRayCaster]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
InputController::~InputController()
{
	delete mRayCaster;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		MouseClick

Summary:	Processes a mouseClick event.

Args:		MouseButtonEvent & evt
				the mouseButtonEvent that warranted this mouseClick call.
			CameraController &camControl.
				a reference to the cameraController being used by the system.
			SceneManager &scnMgr
				a reference to the SceneManager being used by the system.
			Vector3 *& result
				a pointer reference to store the resulant vector 3 in.
			Entity *& collided
				a pointer reference to store the intersected entity in.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void InputController::MouseClick(
	const OgreBites::MouseButtonEvent & evt,
	const CameraController &camControl,
	Ogre::SceneManager &scnMgr,
	Ogre::Vector3 *& result,
	Ogre::Entity *& collided)
{
	// Temporary storage for a ray.	
	Ogre::Ray ray;

	// Use the cameraController to obtain the ray.
	camControl.GetCameraToViewportRay(evt.x, evt.y, &ray);

	// Use the raycaster object to perform a raycast and store in result and collided.
	mRayCaster->RayCast(ray, *result, collided, scnMgr);
}
