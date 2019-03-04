#include "Ogre3DApplication.h"


void Ogre3DApplication::setupUITray(const Ogre::String & name, Ogre::RenderWindow * window)
{
	//By default the Tray uses the overlay configuration in the file SdkTrays.overlay.
	//You can locate this file in media/packs/SdkTrays.zip
	//Unless you REALLY want to reskin the UI, I would recommend using the default overlay configuration as it has
	//already defined some common UI elements.
	mTrayManager = new OgreBites::TrayManager("UITray", window, this);

	//Add a button
	OgreBites::Button* quitBttn = mTrayManager->createButton(OgreBites::TL_BOTTOMLEFT, "QuitBTN", "Quit");
	
	//Add a label
	OgreBites::Label* titleLB = mTrayManager->createLabel(OgreBites::TL_TOP, "TitleLB", "CIT2213\nOgre3DProjTemplate");
	
	//show the frame stat box
	//N.B. the frame stat box is created by TrayManager by default.
	mTrayManager->showFrameStats(OgreBites::TL_TOPRIGHT);

	mTrayManager->setTrayPadding(10.0f);

	mTrayManager->showAll();

}

Ogre3DApplication::Ogre3DApplication()
: OgreBites::ApplicationContext("CIT2213 Ogre3D Template")
{
	
}

Ogre3DApplication::~Ogre3DApplication()
{

}

void Ogre3DApplication::setup()
{
	// do not forget to call the base first
	OgreBites::ApplicationContext::setup();

	//Initialise the resource group labeled Essential
	//N.B. all resource groups are defined in the file resources.cfg or resources_d.cfg
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");

	// register for input events
	addInputListener(this);

	// get a pointer to the already created root
	Ogre::Root* root = getRoot();
	Ogre::SceneManager* scnMgr = root->createSceneManager();

	scnMgr->addRenderQueueListener(mOverlaySystem);

	// register our scene with the RTSS
	Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// without light we would just get a black screen    
	Ogre::Light* light = scnMgr->createLight("MainLight");
	Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(0, 10, 15);
	lightNode->attachObject(light);

	// also need to tell where we are
	Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 0, 15);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

	// create the camera
	Ogre::Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);

	// finally something to render
	Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
	Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);
	node->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(Ogre::Degree(45.0f)));

	setupUITray("TemplateUI", this->getRenderWindow());

}

void Ogre3DApplication::shutdown()
{
	//Clean up any resources created by this application
	//e.g. TrayManager was created specifically here
	delete mTrayManager;

	ApplicationContext::shutdown();
}

bool Ogre3DApplication::frameRenderingQueued(const Ogre::FrameEvent & evt)
{
	mTrayManager->frameRendered(evt);

	try
	{
		return ApplicationContext::frameRenderingQueued(evt);
	}
	catch (Ogre::Exception& e)   // show error and fall back to menu
	{
		mTrayManager->showOkDialog("Error!", e.getDescription() + "\nSource: " + e.getSource());
	}

	return true;
}

void Ogre3DApplication::frameRendered(const Ogre::FrameEvent & evt)
{
	mTrayManager->frameRendered(evt);
}

bool Ogre3DApplication::keyPressed(const OgreBites::KeyboardEvent & event)
{
	if (event.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}

	return true;
}

bool Ogre3DApplication::keyReleased(const OgreBites::KeyboardEvent & evt)
{
	return true;
}

bool Ogre3DApplication::mouseMoved(const OgreBites::MouseMotionEvent & evt)
{
	if (mTrayManager->mouseMoved(evt))
		return true;

	return true;
}

bool Ogre3DApplication::mouseWheelRolled(const OgreBites::MouseWheelEvent & evt)
{
	if (mTrayManager->mouseWheelRolled(evt))
		return true;

	return true;
}

bool Ogre3DApplication::mousePressed(const OgreBites::MouseButtonEvent & evt)
{
	if (mTrayManager->mousePressed(evt))
		return true;

	return true;
}

bool Ogre3DApplication::mouseReleased(const OgreBites::MouseButtonEvent & evt)
{
	if (mTrayManager->mouseReleased(evt))
		return true;

	return true;
}

void Ogre3DApplication::buttonHit(OgreBites::Button * button)
{
	//Handle button hit event.
	Ogre::String bttnName = button->getName();

	if (bttnName == "QuitBTN")
	{
		getRoot()->queueEndRendering();
	}
}

void Ogre3DApplication::itemSelected(OgreBites::SelectMenu * menu)
{
}

void Ogre3DApplication::labelHit(OgreBites::Label * label)
{
}

void Ogre3DApplication::sliderMoved(OgreBites::Slider * slider)
{
}

void Ogre3DApplication::checkBoxToggled(OgreBites::CheckBox * box)
{
}

void Ogre3DApplication::okDialogClosed(const Ogre::DisplayString & message)
{
}

void Ogre3DApplication::yesNoDialogClosed(const Ogre::DisplayString & question, bool yesHit)
{
}
