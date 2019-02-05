#pragma once

#include <Ogre.h>
#include <Bites/OgreApplicationContext.h>

class Ogre3DApplication : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	Ogre3DApplication();
	~Ogre3DApplication();

	void setup() override;
	bool keyPressed(const OgreBites::KeyboardEvent& event) override;
};

