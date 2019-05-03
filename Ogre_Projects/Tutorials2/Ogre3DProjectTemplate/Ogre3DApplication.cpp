//=====================================================
//				Filenae: Ogre3DApplication.cpp
//=====================================================


//=====================================================
//				Defined Includes.
//=====================================================
#include "Ogre3DApplication.h"
#include "AStar.h"
#include "CameraController.h"
#include "InputController.h"
#include "Tile.h"
#include "TileManager.h"
#include "Agent.h"


//=====================================================
//				Library Includes.
//=====================================================
#include <OgreColourValue.h>
#include <OGRE/OgreConfigFile.h>
#include <OgreStaticGeometry.h>
#include <Bites/OgreTrays.h>


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
  Method:	Ogre3DApplication

  Summary:	Constructor for a default Ogre3D Application context window.

  Args:		Member_Initializer_List:	OgreBites::ApplicationContext("TutorialApp")
											Sets the window name in the parent OgreBites ApplicationContext variable to "TutorialApp"
											i.e. The Window will be called "TutorialApp"

  Modifies:	[ALL MEMBERS]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Ogre3DApplication::Ogre3DApplication() : OgreBites::ApplicationContext("TutorialApp")
{
	mInControl = NULL;
	mCamControl = NULL;
	g_ScnMgr = nullptr;
	mTileMgr = NULL;
	mAgent = NULL;
	mTrayManager = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
  Method:	~Ogre3DApplication

  Summary:	The deconstructor for an Ogre3DApplication Instance.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Ogre3DApplication::~Ogre3DApplication()
{
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		keyPressed()

Summary:	Takes in an input from the keyboard and handles it appropriately.
				In this case, if the user hits escape, get the Root node of the Ogre3D application and stop it from rendering.

Args:		OgreBites::KeyboardEvent & evt
				a KeyboardEvent object representing the keyPressed that called this method.

Returns:	bool
				always true to indicate there is no way to fail this method.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
bool Ogre3DApplication::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	// If the user presses escape.
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		// Get the root of the ogre rendering system and ask it to stop rendering.
		getRoot()->queueEndRendering();
	}

	// Return true that the keypress executed succesfully.
	return true;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		mouseWheelRolled

Summary:	Handles the mouseWheelBeing rolled.

Args:		MouseWheelEvent & evt
				the mouseWheelEvent causing this function call.

Returns:	bool
				did this action execute successfully?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
bool Ogre3DApplication::mouseWheelRolled(const OgreBites::MouseWheelEvent & evt)
{
	// Ask the mCamControl to zoom using the mouseWheel scroll delta.
	mCamControl->Zoom(evt.y);

	// Return true that the mouseWheel executed successfully.
	return true;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		mousePressed

Summary:	Handle the mouse buttons being pressed.

Args:		MouseButtonEvent & evt
				the mouseButtonEvent causing this function call.

Returns:	bool
				did this action execute successfully?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
bool Ogre3DApplication::mousePressed(const OgreBites::MouseButtonEvent & evt)
{
	// Create storage for a resultant vector and entity.
	Ogre::Vector3* result = new Ogre::Vector3();
	Ogre::Entity* collided = NULL;

	// Ask the input controller to process a mouseClick using the information.
	mInControl->MouseClick(evt, *mCamControl, *g_ScnMgr, result, collided);

	// If a result was found from the mouseclick.
	if (collided != NULL)
	{
		// Create storage for a Tile and attempt to find it using the collided with entity.
		Tile* tileCollided = NULL;
		mTileMgr->Find(tileCollided, *collided);

		// If a tile was found AND the agent is not currently on said tile...
		if (tileCollided != NULL && tileCollided->GetNode() != mAgent->GetNode())
		{
			// Process each button type differently.
			switch (evt.button)
			{
			case OgreBites::BUTTON_LEFT:

				// Ask the tileManager to cycle the clicked on tile.
				mTileMgr->CycleTile(tileCollided);
				break;
			case OgreBites::BUTTON_RIGHT:

				// If the tile is a grass one, Ask the agent to set its current Tile to the clicked on one.
				if (tileCollided->GetState() == Tile::TILE_GRASS)
					mAgent->SetNode(tileCollided->GetNode());
				break;
			case OgreBites::BUTTON_MIDDLE:

				// Ask the tile manager to set the clicked on tile as the goal tile.
				mTileMgr->SetGoal(tileCollided);
				break;
			}
		}
	}

	// Run the mousePress through the trayManager and return true that this action executed successfully.
	if(mTrayManager->mousePressed(evt))
		return true;

	// Return true that this action executed successfully.
	return true;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		mouseReleased

Summary:	Handle the releasing of mouseButtons.

Args:		MouseButtonEvent & evt
				the mouseButtonEvent that caused this function call.

Returns:	bool
				did this action execute successfully?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
bool Ogre3DApplication::mouseReleased(const OgreBites::MouseButtonEvent & evt)
{
	// Run the mouseevent through the tray manager and return true.
	if (mTrayManager->mouseReleased(evt))
		return true;

	// Return true that this action executed successfully.
	return true;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		mouseMoved

Summary:	Handle the movement of the mouse cursor.

Args:		MouseMotionEvent & evt
				the mouseMotionEvent that cause this function call.

Returns:	bool
				did this action execute successfully?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
bool Ogre3DApplication::mouseMoved(const OgreBites::MouseMotionEvent & evt)
{
	// Run the mouseMotionEvent through the trayManager and retrn true.
	if (mTrayManager->mouseMoved(evt))
		return true;

	// Return true that this action executed successfully.
	return true;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		FrameRendered

Summary:	Handle a frame being rendered.

Args:		FrameEvent & evt
				the FrameEvent that caused this function call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Ogre3DApplication::frameRendered(const Ogre::FrameEvent & evt)
{
	// run the frameEvent through the traymanager.
	mTrayManager->frameRendered(evt);
}



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		setup()

Summary:	Sets this object and a base scene up.

Modifies:	[g_ScnMgr, mCamControl, mTileMgr, mAgent, mInControl]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Ogre3DApplication::setup()
{
	using namespace Ogre;

	// Setup the base application frame.
#pragma region 1. ApplicationSetup
	
	// Call the base setup in Application Context First.
	OgreBites::ApplicationContext::setup();

	// register for input events.
	addInputListener(this);

#pragma endregion

	// Create the base elements for the scene.
#pragma region 2. Create Base Scene.

	// Get the Root and create a sceneManager using this.
	Root* root = getRoot();
	g_ScnMgr = root->createSceneManager();

	// Add the overlay system to the rendering queue listener.
	g_ScnMgr->addRenderQueueListener(mOverlaySystem);

	//Register our 'scene' with the 'Run-Time Shader System' (RTSS)
	/// - Get the singleton RTSS shaderGenerator -> then add our created sceneManager to it.
	RTShader::ShaderGenerator* shaderGen = RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(g_ScnMgr);

	// Setup the mCamera controller.
	mCamControl = new CameraController(*g_ScnMgr, *this);

#pragma endregion

	// Add some objects to render in the scene.
#pragma region 3. Add objects to render.

	// Load all resources required.
	SetupResources();

	// Create the tilemanager.
	mTileMgr = new TileManager();

	// The name of the default tile mesh.
	String nameOfTile = "GrassTile.mesh";

	// The gridsize to be used.
	int gridSize = 20;
	int numberOfEntities = gridSize * gridSize;

	// For every entity.
	for (int i = 0; i < numberOfEntities; i++)
	{
		// Calculate its z and x position (unit position)
		int zOffsetMultiplier = (i / gridSize);
		int xOffsetMultiplier = (zOffsetMultiplier % 2 == 0) ? (i % gridSize) * 2 : ((i % gridSize) * 2) + 1;
		zOffsetMultiplier *= 2;

		// Grab the offset values from the tileManager.
		Ogre::Real xOffset = TileManager::xOffset;
		Ogre::Real zOffset = TileManager::zOffset;

		// Create positional data using the calculated values.
		Vector3 position(xOffsetMultiplier * xOffset, 0, zOffsetMultiplier * zOffset);
		Quaternion quat(Radian(Degree(-90)), Vector3::UNIT_X);

		// Create the tile using the Grass material and the calculated positional data.
		Tile* tile = new Tile(*g_ScnMgr, nameOfTile, "Grass", position, quat);

		// Add the tile into consideration by the tile manager.
		mTileMgr->Add(*tile);
	}

	// Finally create the agent on screen.
	mAgent = new Agent(g_ScnMgr);

#pragma endregion

	//Make some tweaks to the lighting.
#pragma region 4. change the base lighting setting.

	//Change the light colour.
	g_ScnMgr->setAmbientLight(ColourValue(0, 0, 0));

	//Set the shadow method to be used.
	g_ScnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);

#pragma endregion

	//Create some more advanced lighting.
#pragma region 5. Add lights.

	// Create a light.
	Light* dirLight = g_ScnMgr->createLight("directionalLight");
	{
		//Setup type and values.
		dirLight->setType(Light::LightTypes::LT_DIRECTIONAL);

		dirLight->setDiffuseColour(1, 1, 1);
		dirLight->setSpecularColour(1, 1, 1);
	}

	//Create the node for the directional light.
	SceneNode* dirLightNode = g_ScnMgr->getRootSceneNode()->createChildSceneNode();
	{
		//Setup attachment and values.
		///Directional lights do not need positions.
		//dirLightNode->attachObject(dirLight);
		dirLightNode->setDirection(Vector3(0, -1, -1));
	}


#pragma endregion

	// set up the input controller.
#pragma region 6. Input Controller setup

	// Create the input Controller.
	mInControl = new InputController();

#pragma endregion

	// Setup the UI system.
#pragma region 7. UI setup.

	// Setup the UI
	setupUITray("AStar Demonstration", this->getRenderWindow());

#pragma endregion

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		frameRenderingQueued

Summary:	Handle a frame being queued for rendering.

Args:		FrameEvent & evt
				the frame event that caused this function call.

Returns:	bool
				did this action execute successfully?
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
bool Ogre3DApplication::frameRenderingQueued(const Ogre::FrameEvent & evt)
{
	// Pass the frame event through the trayManager.
	mTrayManager->frameRendered(evt);

	try
	{
		// Try to return the frame event passed through the ApplicationContext.
		return ApplicationContext::frameRenderingQueued(evt);
	}
	catch (Ogre::Exception& e)   // show error and fall back to menu
	{
		mTrayManager->showOkDialog("Error!", e.getDescription() + "\nSource: " + e.getSource());
	}

	// Return true that the action executed succesfully.
	return true;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		buttonHit

Summary:	Handle a button being pressed.

Args:		Button * button
				a pointer to the button that was pressed.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Ogre3DApplication::buttonHit(OgreBites::Button * button)
{
	//Handle button hit event.
	Ogre::String bttnName = button->getName();

	if (bttnName == "QuitBTN")
	{
		// If quit button, ask the root to stop rendering.
		getRoot()->queueEndRendering();
	}
	else if (bttnName == "GoBTN")
	{
		// If go button, ask the agent to pathfind using the stored tileManager.
		mAgent->PathFind(mTileMgr);
	}
	else if (bttnName == "ResetBTN")
	{
		// If reset button, ask the tileManger to reset every tile, and reset the agent.
		mTileMgr->ResetTiles();
		mAgent->Reset();
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		SetupResources

Summary:	Use before entity creation to load in all the resources on file.

NOTE:		Taken From Ogre Forums. Original Source lost. Code is NOT my work 
			Author:			<unknown>
			Date:			<unknown>
			Code Version:	<unknown>
			Availability:	<Ogre forums>
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
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


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		setupUITray

Summary:	Setup and display the base UI

Args:		RenderWindow * window
				a pointer to the renderwindow being used.

Modifies:	[mTrayManager]

NOTE:		Taken from Ogre3DProjectTemplate. Code is NOT my work.
			Author:			<Minsi Chen>
			Date:			<10.02.2019>
			Code Version:	<1.0>
			Availability:	<https://brightspace.hud.ac.uk/d2l/le/content/9617/viewContent/192021/View>
			Modifications:
				Modified parameters passed to constructors.
				Added goBttn and ResetBttn.
				Added explanationTB
				ReCommented code as per internal standard.
				Removed unrequired parameters.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Ogre3DApplication::setupUITray(Ogre::RenderWindow * window)
{
	// Create the tray manager.
	mTrayManager = new OgreBites::TrayManager("UITray", window, this);

	// Add the quit, go and reset buttons.
	OgreBites::Button* quitBttn = mTrayManager->createButton(OgreBites::TL_BOTTOMLEFT, "QuitBTN", "Quit");
	OgreBites::Button* goBttn = mTrayManager->createButton(OgreBites::TL_LEFT, "GoBTN", "Go!");
	OgreBites::Button* ResetBttn = mTrayManager->createButton(OgreBites::TL_BOTTOM, "ResetBTN", "Reset");

	// Add the title label.
	OgreBites::Label* titleLB = mTrayManager->createLabel(OgreBites::TL_TOP, "TitleLB", "The AI revolution", 200);

	// Add the explanation text box.
	OgreBites::TextBox* explanationTB = mTrayManager->createTextBox(OgreBites::TL_TOPLEFT, "ExplanationLB", "Explanation:\n\nLMB: Change tile between mountain and grass\n    Mountain: Impassable\n    Grass: Passable\n\nRMB: Change position of Sinbad.\n\nMMB: Set Goal Tile.\n\n\nHit Go for sinbad to find his way\nto the goal tile!", 375, 225);

	//show the frame stat box
	//N.B. the frame stat box is created by TrayManager by default.
	mTrayManager->showFrameStats(OgreBites::TL_TOPRIGHT);

	mTrayManager->setTrayPadding(10.0f);

	mTrayManager->showAll();

}

