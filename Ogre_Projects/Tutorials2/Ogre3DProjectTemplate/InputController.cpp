#include "InputController.h"
#include "RayCasting.h"
#include "CameraController.h"

#include <OgreMath.h>
#include <OgreVector3.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreRay.h>



InputController::InputController()
{
	rayCaster = new RayCasting();
}


InputController::~InputController()
{
	delete rayCaster;
}

void InputController::MouseClick(
	const OgreBites::MouseButtonEvent & evt,
	const CameraController &camControl,
	Ogre::SceneManager &scnMgr,
	Ogre::Vector3 *& result,
	Ogre::Entity *& collided)
{
	Ogre::Ray ray;
	camControl.GetCameraToViewportRay(evt.x, evt.y, &ray);

	rayCaster->RayCast(ray, result, collided, scnMgr);
}
