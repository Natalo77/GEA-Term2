#pragma once


#ifndef _CAMCONTROL_H_
#define _CAMCONTROL_H_

namespace Ogre
{
	class SceneManager;
	class SceneNode;
	class Camera;
	class Viewport;
	class Ray;
}

#include <OGRE/OgreMath.h>




class Ogre3DApplication;


const Ogre::Real INITIAL_CAM_X = 1140;
const Ogre::Real INITIAL_CAM_Y = 3000;
const Ogre::Real INITIAL_CAM_Z = 950;

const int SCROLL_SPEED_MULTIPLIER = 1000;


class CameraController
{
public:
	CameraController();
	~CameraController();
	CameraController(Ogre::SceneManager& scnMgrRef, Ogre3DApplication& parent);

	void Zoom(int value);

	Ogre::Vector3 GetDirection() const;

	void GetCameraToViewportRay(Ogre::Real x, Ogre::Real y, Ogre::Ray* out) const;
	
private:
	Ogre::Real getAspectRatio();



private:
	Ogre::SceneNode* camNode;

	Ogre::Camera* camera;

	Ogre::Viewport* viewPort;

	Ogre::SceneManager* scnMgr;
};

#endif

