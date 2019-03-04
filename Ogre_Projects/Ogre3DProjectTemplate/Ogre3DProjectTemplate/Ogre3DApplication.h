#pragma once

#include <Ogre.h>
#include <Bites/OgreTrays.h>
#include <Bites/OgreApplicationContext.h>
#include <Overlay/OgreFont.h>

class Ogre3DApplication : public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener
{
private:
	OgreBites::TrayManager* mTrayManager; 
	
	void setupUITray(const Ogre::String& name, Ogre::RenderWindow *window);
	
public:
	Ogre3DApplication();
	~Ogre3DApplication();

	//The following methods are virtual functions from ApplicationContext
	void setup() override;
	void shutdown() override;
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;


	//The following methods are virtual functions from InputListener
	//You can override them to customise how your application respond to various inputs.
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& event) override;
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;
	virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) override;
	virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt) override;
	virtual bool mouseReleased(const OgreBites::MouseButtonEvent& evt) override;

	//The following methods are virtual functions from TrayListener
	//You can override them to customise how your application respond to UI items event
	virtual void buttonHit(OgreBites::Button* button) override;
	virtual void itemSelected(OgreBites::SelectMenu* menu) override;
	virtual void labelHit(OgreBites::Label* label) override;
	virtual void sliderMoved(OgreBites::Slider* slider) override;
	virtual void checkBoxToggled(OgreBites::CheckBox* box) override;
	virtual void okDialogClosed(const Ogre::DisplayString& message) override;
	virtual void yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit) override;
};

