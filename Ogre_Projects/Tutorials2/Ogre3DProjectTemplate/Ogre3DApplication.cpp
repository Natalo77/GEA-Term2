//=====================================================
//				Filenae: Ogre3DApplication.cpp
//=====================================================


//=====================================================
//				Defined headers.
//=====================================================
#include "Ogre3DApplication.h"
#include "AStar.h"
#include "CameraController.h"
#include "InputController.h"
#include "Tile.h"
#include "TileManager.h"
#include "Agent.h"


//=====================================================
//				Libraries
//=====================================================
#include <OgreColourValue.h>
#include <OGRE/OgreConfigFile.h>
#include <OgreStaticGeometry.h>
#include <Bites/OgreTrays.h>



//Ogre3DApplication()
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
  Method:	Ogre3DApplication::Ogre3DApplication

  Summary:	Constructor for a default Ogre3D Application context window.

  Args:		Member_Initializer_List:	OgreBites::ApplicationContext("TutorialApp")
											Sets the window name in the parent OgreBites ApplicationContext variable to "TutorialApp"
											i.e. The Window will be called "TutorialApp"

  Returns:	An Instance of Ogre3DApplication
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Ogre3DApplication::Ogre3DApplication() : OgreBites::ApplicationContext("TutorialApp")
{
	inControl = NULL;
}

//~Ogre3DApplication()
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
  Method:		Ogre3DApplication::~Ogre3DApplication

  Summary:	The deconstructor for an Ogre3DApplication Instance.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Ogre3DApplication::~Ogre3DApplication()
{
}

//keyPressed()
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		Ogre3DApplication::keyPressed()
				Overriden from OgreBits::InputListener

Summary:	Takes in an input from the keyboard and handles it appropriately.
				In this case, if the user hits escape, get the Root node of the Ogre3D application and stop it from rendering.

Args:		OgreBites::KeyboardEvent & evt
				a KeyboardEvent object representing the keyPressed that called this method.

Returns:	bool
				always true to indicate there is no way to fail this method.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
bool Ogre3DApplication::keyPressed(const OgreBites::KeyboardEvent & evt)
{

#pragma region 1. Handle Escape Key
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	return true;
#pragma endregion

}

bool Ogre3DApplication::mouseWheelRolled(const OgreBites::MouseWheelEvent & evt)
{
	camControl->Zoom(evt.y);
	return true;
}

bool Ogre3DApplication::mousePressed(const OgreBites::MouseButtonEvent & evt)
{
	Ogre::Vector3* result = new Ogre::Vector3();
	Ogre::Entity* collided = NULL;

	inControl->MouseClick(evt, *camControl, *scnMgr, result, collided);

	if (result != NULL && collided != NULL)
	{
		Tile* tileCollided = NULL;
		tileMgr->Find(tileCollided, *collided);

		if (tileCollided != NULL && tileCollided->GetNode() != mAgent->GetNode())
			switch (evt.button)
			{
			case OgreBites::BUTTON_LEFT:
				tileMgr->CycleTile(tileCollided);
				break;
			case OgreBites::BUTTON_RIGHT:
				if(tileCollided->GetState() == Tile::TILE_GRASS)
					mAgent->SetNode(tileCollided->GetNode());
				break;
			case OgreBites::BUTTON_MIDDLE:
				tileMgr->SetGoal(tileCollided);
				break;
			}
			

		
	}

	if(mTrayManager->mousePressed(evt))
		return true;

	return true;
}


bool Ogre3DApplication::mouseReleased(const OgreBites::MouseButtonEvent & evt)
{
	if (mTrayManager->mouseReleased(evt))
		return true;

	return true;
}


bool Ogre3DApplication::mouseMoved(const OgreBites::MouseMotionEvent & evt)
{
	if (mTrayManager->mouseMoved(evt))
		return true;

	return true;
}


void Ogre3DApplication::frameRendered(const Ogre::FrameEvent & evt)
{
	mTrayManager->frameRendered(evt);
}


//setup()
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		setup()
				overriden from OgreBits::ApplicationContext.

Summary:	Handles the setup of a basic scene.
				Creates a default Ogre3D application.
				Creates a base scene
					Create a scene and register it with the RunTimeShaderSystem (RTSS)
					Setup a light object
					Setup a camera
				Add objects for the system to render and view.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Ogre3DApplication::setup()
{
	using namespace Ogre;

	//Setup the base application frame.
#pragma region 1. ApplicationSetup
	//Call the base setup in Application Context First.
	OgreBites::ApplicationContext::setup();

	//register for input events.
	addInputListener(this);
#pragma endregion

	//Create the base elements for the scene.
#pragma region 2. Create Base Scene.

	//Create the scene itself and register it with the Shader.
#pragma region 2.1 Create the scene and register it with the RTSS
	//Create our scene.
	///Get a pointer to the root node -> then create a scene Manager within that node.
	Root* root = getRoot();
	scnMgr = root->createSceneManager();


	// Add the overlay system to the rendering queue listener.
	scnMgr->addRenderQueueListener(mOverlaySystem);

	//Register our 'scene' with the 'Run-Time Shader System' (RTSS)
	/// - Get the singleton RTSS shaderGenerator -> then add our created sceneManager to it.
	RTShader::ShaderGenerator* shaderGen = RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(scnMgr);
#pragma endregion.

	//Setup our camera.
#pragma region 2.2 Setup the camera.

	// Setup the camera controller.
	camControl = new CameraController(*scnMgr, *this);

#pragma endregion

#pragma endregion

	//Add some objects to render in the scene.
#pragma region 3. Add objects to render.

	// Load all resources required.
	SetupResources();

	// Create the tilemanager.
	tileMgr = new TileManager();

	// Load the tiles.
#pragma region 3.1 Loading Tiles for level

	String nameOfTile = "GrassTile.mesh";
	int gridSize = 20;
	int numberOfEntities = gridSize * gridSize;
	
	// StaticGeometry* tileNodeGeometry = scnMgr->createStaticGeometry("TilesArea");

	for (int i = 0; i < numberOfEntities; i++)
	{
		int zOffsetMultiplier = (i / gridSize);
		int xOffsetMultiplier = (zOffsetMultiplier % 2 == 0) ? (i % gridSize) * 2 : ((i % gridSize) * 2) + 1;
		zOffsetMultiplier *= 2;

		Ogre::Real xOffset = TileManager::xOffset;
		Ogre::Real zOffset = TileManager::zOffset;

		Vector3 position(xOffsetMultiplier * xOffset, 0, zOffsetMultiplier * zOffset);
		Quaternion quat(Radian(Degree(-90)), Vector3::UNIT_X);

		Tile* tile = new Tile(*scnMgr, nameOfTile, "Grass", position, quat);

		tileMgr->Add(*tile);

		// tileNodeGeometry->addEntity(tile->GetEntity(), position, quat);
	}

	// tileNodeGeometry->build();

#pragma endregion


	// Create the initial agent.
#pragma region 3.2 Agent creation

	mAgent = new Agent(scnMgr);

#pragma endregion

#pragma endregion

	//Make some tweaks to the lighting.
#pragma region 4. change the base lighting setting.

	//Change the light colour.
	///0,0,0 to see the full effect of the lights
	scnMgr->setAmbientLight(ColourValue(0, 0, 0));

	//Set the shadow method to be used.
	scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
	
	

#pragma endregion

	//Create some more advanced lighting.
#pragma region 5. Add lights.

	//Add a directional light.
#pragma region 5.1 Add a directional light.

	Light* dirLight = scnMgr->createLight("directionalLight");
	{
		//Setup type and values.
		dirLight->setType(Light::LightTypes::LT_DIRECTIONAL);

		dirLight->setDiffuseColour(1, 1, 1);
		dirLight->setSpecularColour(1, 1, 1);
	}

	//Create the node for the directional light.
	SceneNode* dirLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		//Setup attachment and values.
		///Directional lights do not need positions.
		//dirLightNode->attachObject(dirLight);
		dirLightNode->setDirection(Vector3(0, -1, -1));
	}
#pragma endregion


#pragma endregion


	// set up the input controller.
#pragma region 6. Input Controller setup

	inControl = new InputController();

#pragma endregion


	// Setup the UI system.
#pragma region 7. UI setup.

	setupUITray("AStar Demonstration", this->getRenderWindow());

#pragma endregion

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


void Ogre3DApplication::buttonHit(OgreBites::Button * button)
{
	//Handle button hit event.
	Ogre::String bttnName = button->getName();

	if (bttnName == "QuitBTN")
	{
		getRoot()->queueEndRendering();
	}
	else if (bttnName == "GoBTN")
	{
		mAgent->PathFind(tileMgr);
	}

}


void Ogre3DApplication::SetupResources()
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator itSection = cf.getSectionIterator();

	Ogre::String strGroupName, strLocation, strType;
	while (itSection.hasMoreElements())
	{
		// Resource group.  "General", etc
		strGroupName = itSection.peekNextKey();

		Ogre::ConfigFile::SettingsMultiMap* mapSettings = itSection.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator itSetting = mapSettings->begin();

		for (; itSetting != mapSettings->end(); ++itSetting)
		{
			// Zip or FileSystem
			strType = itSetting->first;
			// Filepath
			strLocation = itSetting->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(strLocation, strType, strGroupName);
		}
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Ogre3DApplication::setupUITray(const Ogre::String & name, Ogre::RenderWindow * window)
{
	//By default the Tray uses the overlay configuration in the file SdkTrays.overlay.
	//You can locate this file in media/packs/SdkTrays.zip
	//Unless you REALLY want to reskin the UI, I would recommend using the default overlay configuration as it has
	//already defined some common UI elements.
	mTrayManager = new OgreBites::TrayManager("UITray", window, this);

	//Add a button
	OgreBites::Button* quitBttn = mTrayManager->createButton(OgreBites::TL_BOTTOMLEFT, "QuitBTN", "Quit");

	OgreBites::Button* goBttn = mTrayManager->createButton(OgreBites::TL_LEFT, "GoBTN", "Go!");

	//Add a label
	OgreBites::Label* titleLB = mTrayManager->createLabel(OgreBites::TL_TOP, "TitleLB", "The AI revolution", 200);

	OgreBites::TextBox* explanationTB = mTrayManager->createTextBox(OgreBites::TL_TOPLEFT, "ExplanationLB", "Explanation:\n\nLMB: Change tile between mountain and grass\n    Mountain: Impassable\n    Grass: Passable\n\nRMB: Change position of Sinbad.\n\nMMB: Set Goal Tile.\n\n\nHit Go for sinbad to find his way\nto the goal tile!", 375, 225);

	//show the frame stat box
	//N.B. the frame stat box is created by TrayManager by default.
	mTrayManager->showFrameStats(OgreBites::TL_TOPRIGHT);

	mTrayManager->setTrayPadding(10.0f);

	mTrayManager->showAll();

}

