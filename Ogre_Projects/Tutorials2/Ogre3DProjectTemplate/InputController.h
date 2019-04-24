#pragma once


class RayCasting;
class CameraController;
namespace Ogre {
	class SceneManager;
}

#include <OgreInput.h>

class InputController
{
public:
	InputController();
	~InputController();

	void MouseClick(
		const OgreBites::MouseButtonEvent & evt, 
		const CameraController &camControl,
		Ogre::SceneManager &scnMgr);

private:
	RayCasting* rayCaster;
};

