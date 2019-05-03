//=====================================================
//				Filename: InputController.h
//=====================================================
#pragma once


//=====================================================
//				Forward Declarations.
//=====================================================
class RayCasting;
class CameraController;
namespace Ogre {
	class SceneManager;
	class Entity;
}


//=====================================================
//					Library Includes.
//=====================================================
#include <OgreInput.h>
#include <OgreMath.h>


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    InputController

  Summary:  A Class to control and handle Input by a user.

  Methods:  ====================== PUBLIC ======================
			InputController
				The default constructor of an InputController.
			~InputController
				The default deconstructor of an inputController.

			void MouseClick(MouseButtonEvent &, CameraController &, SceneManager &, Vector3 *&, Entity *&)
				Use to process a mouse Click.

  Members:	====================== PRIVATE ======================
			RayCasting* mRayCaster
				The raycasting utility object used by this inputController.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class InputController
{
public:
	InputController();
	~InputController();

	void MouseClick(
		const OgreBites::MouseButtonEvent & evt, 
		const CameraController &camControl,
		Ogre::SceneManager &scnMgr,
		Ogre::Vector3 *& result,
		Ogre::Entity *& collided);

private:
	RayCasting* mRayCaster;
};

