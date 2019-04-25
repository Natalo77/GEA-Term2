#pragma once


class RayCasting;
class CameraController;
namespace Ogre {
	class SceneManager;
	class Entity;
}

#include <OgreInput.h>
#include <OgreMath.h>

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
	RayCasting* rayCaster;
};

