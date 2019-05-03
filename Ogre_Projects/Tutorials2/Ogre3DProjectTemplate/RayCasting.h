//=====================================================
//				Filename: rayCasting.h
//=====================================================
#pragma once


//=====================================================
//				Forward Declarations.
//=====================================================
namespace Ogre
{
	class SceneManager;
	class Entity;
	class Quaternion;
	class Ray;
}
class Tile;


//=====================================================
//				Library Includes.
//=====================================================
#include <OGRE/OgreMath.h>


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    RayCasting

  Summary:  A utility class that provides implementations of rayCasting
			algorithms.

  Methods:	==================== PUBLIC ====================
			RayCasting
				Default constructor of a rayCasting object.
			~RayCasting
				Default deconstructor of a rayCasting object.

			bool RayCast(Ray &, Vector3 &, Entity *&, SceneManager &)
				Use to rayCast and return a vector and entity intersection.

			==================== PRIVATE ====================
			void GetMeshInformation(Entity *, Vector3 *&, size_t &, usigned long *&, Vector3 &, Quaternion &, Vector3 &)
				Use to return the mesh information from a specified entity.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class RayCasting
{
public:
	RayCasting();
	~RayCasting();

	bool RayCast(
		Ogre::Ray &ray, 
		Ogre::Vector3 & result,
		Ogre::Entity *& collided,
		Ogre::SceneManager& scnMgrRef);

private:
	void GetMeshInformation(
		Ogre::Entity* entity,
		Ogre::Vector3* &vertices,
		size_t &indexCount,
		unsigned long* &indices,
		const Ogre::Vector3& position,
		const Ogre::Quaternion& orient,
		const Ogre::Vector3& scale
	);
};

