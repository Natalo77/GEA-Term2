#pragma once


#ifndef _AGENT_H_
#define _AGENT_H_

class AStar_Node;
class TileManager;
#include "AList.h"
namespace Ogre
{
	class SceneManager;
}

#include <OgreSceneNode.h>
#include <OgreMath.h>
#include <OgreEntity.h>


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

	bool hidden;
};


inline void Agent::HideModel()
{
	Ogre::Vector3 vec(-100, 0, -100);
	mSceneNode->_setDerivedPosition(vec);

	mEntity->setVisible(false);

	hidden = true;
}

#endif

