#pragma once


namespace Ogre
{
	class SceneManager;
	class Entity;
	class Quaternion;
	class Ray;
}
class Tile;

#include <OGRE/OgreMath.h>



class RayCasting
{
public:
	RayCasting();
	~RayCasting();

	bool RayCast(
		Ogre::Ray &ray, 
		Ogre::Vector3 *& result,
		Ogre::Entity *& collided,
		Ogre::SceneManager& scnMgrRef);

private:
	void GetMeshInformation(
		Ogre::Entity* entity,
		Ogre::Vector3* vertices,
		size_t &indexCount,
		unsigned long* indices,
		const Ogre::Vector3& position,
		const Ogre::Quaternion& orient,
		const Ogre::Vector3& scale
	);
};

