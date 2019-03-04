#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <Bites/OgreApplicationContext.h>
#include <Bites/OgreTrays.h>


class Ogre3DApplication : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	//Constructors and deconstructors.
	Ogre3DApplication();
	~Ogre3DApplication();

	//Overriden methods from OgreBits::ApplicationContext:
	virtual void setup() override;

	//Overriden methods from OgreBits::InputListener:
	virtual bool keyPressed(const OgreBites::KeyboardEvent &evt) override;

};