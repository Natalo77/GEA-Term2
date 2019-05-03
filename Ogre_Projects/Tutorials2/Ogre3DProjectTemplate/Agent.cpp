//=====================================================
//					Filename: Agent.cpp
//=====================================================


//=====================================================
//				Library Includes.
//=====================================================
#include <OgreSceneManager.h>


//=====================================================
//					Source Includes.
//=====================================================
#include "Agent.h"
#include "AStar_Node.h"
#include "AStar.h"
#include "TileManager.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		Agent

Summary:	The Default constructor for an Agent.
			The created agent will be unusable.

Modifies:	[mCurrentNode, mEntity, g_scnMgr, mSceneNode, mHidden]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Agent::Agent()
{
	mCurrentNode = NULL;
	mEntity = NULL;
	g_scnMgr = nullptr;
	mSceneNode = NULL;
	mHidden = true;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		~Agent

Summary:	The default deconstructor for an Agent.

Modifies:	[mCurrentNode, mEntity, g_scnMgr, mSceneNode]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Agent::~Agent()
{
	if (mCurrentNode)
		delete mCurrentNode;
	if (mEntity)
		delete mEntity;
	if (mSceneNode)
		delete mSceneNode;
	if (g_scnMgr)
		delete g_scnMgr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		Agent(SceneManager *&)

Summary:	A usable constructor for an Agent object.

Args:		SceneManager *& scnMgr
				a pointer reference to the sceneManager singleton being
				used by the system controlling this Agent.

Modifies:	[mCurrentNode]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Agent::Agent(Ogre::SceneManager *& scnMgr)
{
	// there is no initial node.
	mCurrentNode = NULL;

	// Setup the Ogre rendering representation.
	Setup(scnMgr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		Agent(AStar_Node *&, SceneManager *&)

Summary:	A usable constructor for an Agent object, additionally
			specifying a current Node for the agent.

Args:		AStarNode *& currentNode
				a pointer reference to the currentNode of the agent.
			SceneManager *& scnMgr
				a pointer reference to the sceneManager singleton being
				used by the system controlling this agent.

Modifies:	[mCurrentNode]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
Agent::Agent(AStar_Node *& currentNode, Ogre::SceneManager *& scnMgr)
{
	// Setup the Ogre rendering representation.
	Setup(scnMgr);

	// Set the currentNode properly.
	SetNode(currentNode);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		SetNode

Summary:	Use to Set the currentNode and translate the Ogre rendering
			representation accordingly.

Args:		AStar_Node * node
				a pointer to the node to translate to and store.

Modifies:	[mCurrentNode, mSceneNode, mEntity, mHidden]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Agent::SetNode(AStar_Node * node)
{
	// Set the reference to the current node.
	mCurrentNode = node;

	// Convert the 2D node representation top down to a world space V3.
	Ogre::Vector3* tempVec = new Ogre::Vector3(node->getPosition()->x, 0, node->getPosition()->y);

	// Translate from the current position to the wanted position.
	mSceneNode->translate(*tempVec - mSceneNode->_getDerivedPosition());

	// Adjust height for the Sinbad.mesh model
	mSceneNode->translate(Ogre::Vector3(0, 60, 0));

	// Make the model visible and make a note of this.
	mEntity->setVisible(true);
	mHidden = false;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		GetNode.

Summary:	Use to return a pointer to the currentNode the agent
			is standing on.

Returns:	AStar_Node*
				the stored pointer to an AStar_Node object.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
AStar_Node * Agent::GetNode()
{
	return mCurrentNode;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		PathFind

Summary:	Use to ask the agent to pathfind using the TileManager
			to the goalTile stored within, using the currentTile
			as its starting position.

Args:		TileManager * tileMgr
				a pointer to the tileManager being used by the system
				controlling this agent, containing information about
				the tiles in the domain, and the goalTile.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Agent::PathFind(TileManager * tileMgr)
{
	// If the tiles are ready for traversal and the agent is not hidden(has been placed somewhere).
	if (tileMgr->TilesReadyForTraversal() && !mHidden)
	{
		// Ask the tilemanager to calculate the edges present in the domain.
		tileMgr->SetupEdges();

		// Use the AStar Search method using the currentNode and the goal node from the tilemanager to calculate a path of Nodes.
		AList<AStar_Node*>* path = AStar::AStarSearch(mCurrentNode, tileMgr->GetGoalNode());

		// Traverse this path using the tileMgr.
		Traverse(path, tileMgr);

		// Ask the tileManager to tear down the edges as pathfinding is complete and they are no longer needed.
		tileMgr->TearDownEdges();

		// Clear memory used by the path object.
		/// Note the vector elements are not deleted as the Nodes within are still in scope.
		path->clear();
		delete path;
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		Reset

Summary:	Use to Reset the ogre representation of the agent.]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Agent::Reset()
{
	// Hide the model.
	HideModel();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		Setup

Summary:	Setup the Ogre Rendering representation of this agent.

Args:		SceneManager *& scnMgr
				a pointer reference to the global sceneManager singleton
				to use when creating Ogre rendering objects.

Modifies:	[mg_scnMgr, mSceneNode, mEntity]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Agent::Setup(Ogre::SceneManager *& scnMgr)
{
	// Store the reference to the global scene manager.
	g_scnMgr = scnMgr;

	// use the sceneManager to create a scene Node and store a reference to it.
	mSceneNode = g_scnMgr->getRootSceneNode()->createChildSceneNode();

	// Use the scene manager to create an entity and store a reference to it.
	mEntity = g_scnMgr->createEntity("Sinbad.mesh");

	// Attach the model to the sceneNode.
	mSceneNode->attachObject(mEntity);

	// Hide the model and set it's scale up.
	HideModel();
	mSceneNode->setScale(Ogre::Vector3(10, 10, 10));
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		Traverse

Summary:	Traveses the agent through a given path of nodes, using the	
			given tileManager as data reference.

Args:		AList<AStar_Node*> *& path
				a reference pointer to the AList of nodes to be traversed along.
			TileManager * tileMgr
				A pointer to the tileManager containing the tiles owning
				each of the nodes in path.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
void Agent::Traverse(AList<AStar_Node*>*& path, TileManager * tileMgr)
{
	// Reverse iterate over the list.
	for (std::reverse_iterator<AList<AStar_Node*>::iterator> iter = path->rbegin();
		iter != path->rend();
		iter++)
	{
		// Dereference the iterator.
		AStar_Node* node = *iter;

		// Set the new node.
		SetNode(node);

		// Tell the tileManager that the node has been traversed over.
		tileMgr->SetNodeTraversed(node);
	}
}
