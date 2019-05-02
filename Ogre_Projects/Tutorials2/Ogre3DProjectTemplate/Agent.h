#pragma once


class AStar_Node;
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

private:
	void Setup(Ogre::SceneManager *& scnMgr);

private:
	AStar_Node* mCurrentNode;

	Ogre::Entity* mEntity;

	Ogre::SceneManager* g_scnMgr;

	Ogre::SceneNode* mSceneNode;
};

