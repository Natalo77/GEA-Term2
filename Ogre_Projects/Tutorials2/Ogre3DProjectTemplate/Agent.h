#pragma once


#ifndef _AGENT_H_
#define _AGENT_H_

class AStar_Node;
class TileManager;
#include "AList.h"
namespace Ogre
{
	class Entity;
	class SceneManager;
	class SceneNode;
}


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

private:
	void Setup(Ogre::SceneManager *& scnMgr);

	void Traverse(AList<AStar_Node*> *& path);

private:
	AStar_Node* mCurrentNode;

	Ogre::Entity* mEntity;

	Ogre::SceneManager* g_scnMgr;

	Ogre::SceneNode* mSceneNode;
};

#endif

