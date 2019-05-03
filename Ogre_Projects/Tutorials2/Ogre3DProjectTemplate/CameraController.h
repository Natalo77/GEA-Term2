//=====================================================
//				Filename: CameraController.h
//=====================================================
#pragma once


//=====================================================
//				Include Guards.
//=====================================================
#ifndef _CAMCONTROL_H_
#define _CAMCONTROL_H_


//=====================================================
//				Source Includes.
//=====================================================
#include <OGRE/OgreMath.h>


//=====================================================
//					Forward Declarations.
//=====================================================
namespace Ogre
{
	class SceneManager;
	class SceneNode;
	class Camera;
	class Viewport;
	class Ray;
}
class Ogre3DApplication;


//=====================================================
//					Globals.
//=====================================================
const Ogre::Real INITIAL_CAM_X = 1140;
const Ogre::Real INITIAL_CAM_Y = 3000;
const Ogre::Real INITIAL_CAM_Z = 950;
const int SCROLL_SPEED_MULTIPLIER = 100;


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CameraController

  Summary:  A class to control and interact with a singular mCamera used
			by the system.

  Methods:  ====================== PUBLIC ======================
			CameraController
				The Default constructor of a cameracontroller.
			~CameraController
				The Default deconstructor of a cameraController.
			CameraController(SceneManager *&, Ogre3DApplication *&)
				The preferred constructor of a mCamera controller.

			void Zoom(int value)
				Use to zoom the mCamera in and out based on value

			Vector3 GetDirection() const;
				Use to return the direction of the mCamera.

			void GetCameraToViewPortRay(Real, Real, Ray *)
				Used to get a ray from the mouse cursors into world space.

			====================== PRIVATE ======================
			Real getAspectRatio
				Use to get the aspect ratio of the stored viewport.

Members:	====================== PRIVATE ======================
			SceneNode* mCamNode
				A pointer to the sceneNode used for the mCamera.
			Camera* mCamera
				A pointer to the Camera object controlled by this
				cameraController.
			Viewport* mViewPort
				A pointer to the viewport used by this mCamera.
			SceneManager* g_ScnMgr
				A pointer to the global sceneManager used by the system
				owning this cameraController.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CameraController
{
public:
	CameraController();
	~CameraController();
	CameraController(Ogre::SceneManager * scnMgrRef, Ogre3DApplication * parent);

	void Zoom(int value);

	Ogre::Vector3 GetDirection() const;

	void GetCameraToViewportRay(Ogre::Real x, Ogre::Real y, Ogre::Ray* out) const;
	
private:
	Ogre::Real getAspectRatio();

private:
	Ogre::SceneNode* mCamNode;

	Ogre::Camera* mCamera;

	Ogre::Viewport* mViewPort;

	Ogre::SceneManager* g_ScnMgr;
};

#endif

