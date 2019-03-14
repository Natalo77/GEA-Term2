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

//getAspectRatio()
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		getAspectRatio(Ogre::Viewport* vp)

Summary:	Gets an Ogre::Real value representing the aspect ratio of the passed in viewport.

Args:		vp
				the viewport to calculate the aspect ratio for.

Returns:	Ogre::Real value representing the viewport vp's width/height
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Ogre::Real Ogre3DApplication::getAspectRatio(Ogre::Viewport* vp)
{
	//Return an Ogre::Real number representing the width/height of the viewport.
	return Ogre::Real(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
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
	SceneManager* scnMgr = root->createSceneManager();

	//Register our 'scene' with the 'Run-Time Shader System' (RTSS)
	/// - Get the singleton RTSS shaderGenerator -> then add our created sceneManager to it.
	RTShader::ShaderGenerator* shaderGen = RTShader::ShaderGenerator::getSingletonPtr();
	shaderGen->addSceneManager(scnMgr);
#pragma endregion.

	//Setup our initial lighting.
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

	//Setup our camera.
#pragma region 2.3 Setup the camera.
	//Tell Ogre where the 'player' (camera) is.
#pragma region 2.3.1 Create a scene node for the camera.
	///Create a 'scene node' ready for our camera (from the root node) 
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		///Setup the 'camNode'
		///Set it's position to 0,0,15 xyz -> then ask it to look along the vector 0,0,-1 (down), relative to it's parent (the rootnode)
		camNode->setPosition(200, 300, 400);
		camNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);
		/// - Other options are TS_LOCAL and TS_WORLD (local and world space respectively).
	}
#pragma endregion

	//Create the camera object.
#pragma region 2.3.2 Create the camera object.
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
#pragma endregion
	
	//View the main window!
#pragma region 2.3.3 Set up the viewport
	///tell the 'main render window' to get its rendering from our created 'camera' object
	Viewport* vp = getRenderWindow()->addViewport(cam);
	{
		///Set the background colour of the viewport (black - for lighting).
		vp->setBackgroundColour(ColourValue(0, 0, 0));
	}
	{
		///Set the aspect ratio of the camera according to the aspect ratio of the assigned viewport.
		cam->setAspectRatio(getAspectRatio(vp));
	}
#pragma endregion

#pragma endregion

#pragma endregion

	//Add some objects to render in the scene.
#pragma region 3. Add objects to render.

	/*

	//Standard object.
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

	//Other standard object.
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

	//Scaled object.
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

	//rotated object.
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

	*/

	//Shadows object!
#pragma region 3.5 Shadows on an object.

	//Create the object
#pragma region 3.5.1 Create the ninja.

	///Create an entity from the ninja Mesh object -> then attach it to a new scene node.
	Entity* ninjaEnt = scnMgr->createEntity("ninja.mesh");
	{
		//Set our entity to cast shadows.
		ninjaEnt->setCastShadows(true);
	}
	///All in one line!
	scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ninjaEnt);

#pragma endregion

	//Create the ground for the object.
#pragma region 3.5.2 Create the ground

	//Create a plane orthogonal to the Y axis.
	///Move it 0 along its axis.
	Ogre::Plane groundPlane(Ogre::Vector3::UNIT_Y, 0);

	//Use the Ogre mesh manager to create a plane
	///Using our abstract groundPlane.
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		RGN_DEFAULT,
		groundPlane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z
	);

	//Use the created plane to create an entity and node.
	///"ground" is from the MeshManager using "ground" as the name for the resource. It gets stored where the scene manager can access it.
	Entity* groundEnt = scnMgr->createEntity("ground");
	scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEnt);
	{
		//Don't need shadows for the ground. -> then set the material for the mesh.
		groundEnt->setCastShadows(false);
		groundEnt->setMaterialName("Examples/Rockwall");
	}

#pragma endregion

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

	//Add a spotlight.
#pragma region 5.1 Add a spotlight.

	//Create a spotlight using the scnMgr.
	///The name of the spotlight is SpotLight (WE DON'T SET THE TYPE YET)
	Light* spotLight = scnMgr->createLight("SpotLight");
	{
		//set up some values.
		spotLight->setDiffuseColour(0, 0, 1.0);		///pure blue.
		spotLight->setSpecularColour(0, 0, 1.0);	///pure blue.

		spotLight->setType(Light::LT_SPOTLIGHT);	///Ogre::Light::LightTypes::LT_SPOTLIGHT

		spotLight->setSpotlightRange(Degree(35), Degree(50));	///the fading angles.

		spotLight->setAttenuation(Real(7000000), Real(1.0), Real(0.000014), Real(0.000007));
	}

	//Create a node for the spotLight.
	SceneNode* spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		//Set up properties of the node and attachments.
		spotLightNode->attachObject(spotLight);

		spotLightNode->setDirection(-1, -1, 0);				///Point down on the player.
		spotLightNode->setPosition(Vector3(200, 200, 0));	///Put in suitable position.
	}

#pragma endregion

	//Add a directional light.
#pragma region 5.2 Add a directional light.
	Light* dirLight = scnMgr->createLight("directionalLight");
	{
		//Setup type and values.
		dirLight->setType(Light::LightTypes::LT_DIRECTIONAL);

		dirLight->setDiffuseColour(ColourValue(0.4, 0, 0));		///dark red.
		dirLight->setSpecularColour(ColourValue(0.4, 0, 0));	///dark red.
	}

	//Create the node for the directional light.
	SceneNode* dirLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		//Setup attachment and values.
		///Directional lights do not need positions.
		dirLightNode->attachObject(dirLight);
		dirLightNode->setDirection(Vector3(0, -1, 1));
	}
#pragma endregion

	//Add a point light.
#pragma region 5.3 Add a point light
	//Create a light object.
	Light* pointLight = scnMgr->createLight("pointLight");
	{
		//Set it's values.
		pointLight->setType(Light::LightTypes::LT_POINT);

		///Colours.
		pointLight->setDiffuseColour(0.3, 0.3, 0.3);
		pointLight->setSpecularColour(0.3, 0.3, 0.3);
	}

	//Create the scene node for the light.
	SceneNode* pointLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	{
		//Setup attachment and values.
		pointLightNode->attachObject(pointLight);

		///position.
		pointLightNode->setPosition(Vector3(0, 150, 250));
	}
#pragma endregion

#pragma endregion



}


