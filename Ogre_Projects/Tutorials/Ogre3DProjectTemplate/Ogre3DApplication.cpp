#include "Ogre3DApplication.h"
#include <OgreColourValue.h>

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
  Method:	

  Summary:	

  Args:

  Modifies:

  Returns:	
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/

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

#pragma region 1. ApplicationSetup
	//Call the base setup in Application Context First.
	OgreBites::ApplicationContext::setup();

	//register for input events.
	addInputListener(this);
#pragma endregion

#pragma region 2. Create Base Scene.

#pragma region 2.1 Create the scene and register it with the RTSS
	//Create our scene.
	///Get a pointer to the root node -> then create a scene Manager within that node.
	Root* root = getRoot();
	SceneManager* scnMgr = root->createSceneManager();

	//Register our 'scene' with the 'Run-Time Shader System' (RTSS)
	/// - Get the singleton RTSS shaderGenerator -> then add our created sceneManager to it.
	RTShader::ShaderGenerator* shaderGen = RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(scnMgr);
#pragma endregion.

#pragma region 2.2 Setup a light object.
	/*
	//Without light we would just get a black screen.
	///Create a Light object using our 'scene Manager' -> Then use our 'scene Manager' to get the 'root node' and create a child 'Scene node'
	Light* light = scnMgr->createLight("MainLight");
	SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		///Setup the LightNode.
		///Set it's position to 0,10,15 xyz -> then attach the 'Light object' to the 'SceneNode "lightNode"'
		lightNode->setPosition(0, 10, 15);
		lightNode->attachObject(light);
	}
	*/
#pragma endregion

#pragma region 2.3 Setup the camera.
	//Tell Ogre where the 'player' (camera) is.
	///Create a 'scene node' ready for our camera (from the root node) 
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		///Setup the 'camNode'
		///Set it's position to 0,0,15 xyz -> then ask it to look along the vector 0,0,-1 (down), relative to it's parent (the rootnode)
		camNode->setPosition(0, 100, 500);
		camNode->lookAt(Vector3(0, 0, -1), Node::TS_PARENT);
		/// - Other options are TS_LOCAL and TS_WORLD (local and world space respectively).
	}

	//Create the camera object.
	///Use our 'Scene manager' to create a camera object.
	Camera* cam = scnMgr->createCamera("myCam");
	{
		///Setup the camera object.
		///set the near clip distance to 5 (specific to this example) -> then set the camera to use the automatically provided aspect ratio.
		cam->setNearClipDistance(5);
		cam->setAutoAspectRatio(true);
	}
	{
		///attach the 'camera object' to the 'SceneNode' 'camNode'
		camNode->attachObject(cam);
	}

	//View the main window!
	///tell the 'main render window' to get its rendering from our created 'camera' object
	getRenderWindow()->addViewport(cam);
#pragma endregion

#pragma endregion

#pragma region 3. Add objects to render.

#pragma region 3.1 First object

	//Make something to render!
	///Create an 'entity' object using our 'scene manager' (with the path to the mesh we want to use) -> then create a 'sceneNode' 'entNode' to contain this mesh.
	Entity* ent = scnMgr->createEntity("ogrehead.mesh");
	SceneNode* entNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		///Attach the 'entity' object to our created 'SceneNode'
		entNode->attachObject(ent);
	}

#pragma endregion

#pragma region 3.2 Second object.

	//Add a second object.
	///Setup an entity, attach the mesh -> initialize a node at 84,48,0
	Entity* ogreEntity = scnMgr->createEntity("ogrehead.mesh");
	SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(84, 48, 0));
	{
		//attach the object to the node.
		ogreNode->attachObject(ogreEntity);
	}

#pragma endregion

#pragma region 3.3 Scaling an object!

	//Add a third object to demonstrate scaling.
	///setup an entity and its scene object.
	Entity* ent3 = scnMgr->createEntity("ogrehead.mesh");
	SceneNode* ent3Node = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		//Set the position and the scale.
		///attach the object to its scene node.
		ent3Node->setPosition(0, 104, 0);
		ent3Node->setScale(2, 1.2, 1);
		ent3Node->attachObject(ent3);
	}

#pragma endregion

#pragma region 3.4 rotating an object!

	//Add a fourth object to demonstrate rotation.
	///Entity and Scene node.
	Entity* rotEnt = scnMgr->createEntity("ogrehead.mesh");
	SceneNode* rotEntNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		//Set up its position and rotation.
		rotEntNode->setPosition(-84, 48, 0);
		rotEntNode->roll(Degree(-90));
		rotEntNode->attachObject(rotEnt);
	}

#pragma endregion

#pragma endregion

#pragma region 4. change the lighting.

	//Change the light colour.
	///0.5 of red, green and blue.
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	//Create a new Light.
	///Use the scene manager to create a light object. -> then create a child scene node attached to the root node.
	Light* lightTwo = scnMgr->createLight("MainLight2");
	SceneNode* lightNodeTwo = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		//Setup attachment.
		///attach the light object to the light node. -> then set the position of the node.
		lightNodeTwo->attachObject(lightTwo);
		lightNodeTwo->setPosition(20, 80, 50);
	}

#pragma endregion

}


