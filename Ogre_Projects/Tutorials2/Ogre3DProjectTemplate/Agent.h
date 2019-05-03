//=====================================================
//				Filename: Agent.h
//=====================================================
#pragma once


//=====================================================
//					Include Guards.
//=====================================================
#ifndef _AGENT_H_
#define _AGENT_H_


//=====================================================
//				Forward Declarations.
//=====================================================
class AStar_Node;
class TileManager;
namespace Ogre{
	class SceneManager;
}


//=====================================================
//					Library Includes.
//=====================================================
#include <OgreSceneNode.h>
#include <OgreMath.h>
#include <OgreEntity.h>


//=====================================================
//					Source Includes
//=====================================================
#include "AList.h"


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Agent

  Summary:  A Class to represent and control the Sinbad agent used by
			the game system.

  Methods:  ====================== PUBLIC ======================
			Agent()
				The default constructor for an Agent.
			~Agent()
				The default deconstructor for an Agent.
			Agent(SceneManager)
				The constructor for an Agent with a pointer reference to the 
				sceneManager singleton.
			Agent(AStarNode, SceneManager)
				The constructor for an Agent with a predefined Node along with
				the SceneManager singleton *&

			void SetNode(AStar_Node)
				Use to set this Agent's Node. Automatically translates the agent
				to the Node's position.
			AStar_Node* GetNode()
				Use to return a pointer to the Node this agent is currently on.

			void PathFind(TileManager*)
				Use to start pathfinding using a TileManager pointer containing
				information about all the tiles and a goalTile.

			void Reset()
				Use to reset the agent before running another pathfinding operation.


			====================== PRIVATE ======================
			void Setup(SceneManager)
				Used by constructors to setup the Ogre representation of the agent.

			void Traverse(AList<AStarNode>*, TileManager*)
				Traverses this node along a given path, consisting of tiles within tileManager.

			inline void HideModel()
				Hides the Ogre representation of the agent.

Members:	====================== PRIVATE ======================
			AStar_Node* mCurrentNode
				a pointer to the AStar_Node this agent is currently at.

			Entity* mEntity
				a pointer to the Entity used to represent this agent.
			SceneManager* g_scnMgr
				a pointer to the global sceneManager being used by the system this agent
				is controlled by.
			SceneNode* mSceneNode
				a pointer to the sceneNode used to Control this agent's entity.

			bool mHidden
				a bool to represent whether this agent is currently on screen or not.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Agent
{
public:
	Agent();
	~Agent();
	Agent(Ogre::SceneManager *& scnMgr);
	Agent(AStar_Node *& currentNode, Ogre::SceneManager *& scnMgr);

	void SetNode(AStar_Node * node);
	AStar_Node* GetNode();

	void PathFind(TileManager * tileMgr);

	void Reset();

private:
	void Setup(Ogre::SceneManager *& scnMgr);

	void Traverse(AList<AStar_Node*> *& path, TileManager * tileMgr);

	inline void HideModel();

private:
	AStar_Node* mCurrentNode;

	Ogre::Entity* mEntity;
	Ogre::SceneManager* g_scnMgr;
	Ogre::SceneNode* mSceneNode;

	bool mHidden;
};


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++
Method:		HideModel

Summary:	Hides the Model used to represent the agent.
			Moves it out of view.
			Makes it invisible
			Sets hidden to true

Modifies:	[mHidden]
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---*/
inline void Agent::HideModel()
{
	Ogre::Vector3 vec(-100, 0, -100);
	mSceneNode->_setDerivedPosition(vec);

	mEntity->setVisible(false);

	mHidden = true;
}

#endif

