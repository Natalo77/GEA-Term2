

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSubMesh.h>
#include <OgreSubEntity.h>
#include <OgreMesh.h>
#include <OgreRay.h>


#include "RayCasting.h"



RayCasting::RayCasting()
{
}


RayCasting::~RayCasting()
{
}

bool RayCasting::RayCast(
	Ogre::Ray &ray,
	Ogre::Vector3 & result, 
	Ogre::Entity *& collided,
	Ogre::SceneManager& scnMgrRef)
{
	// Create a ray scene query object.
	Ogre::RaySceneQuery* sceneQueryRay = scnMgrRef.createRayQuery(Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
	sceneQueryRay->setSortByDistance(true);

	// check we are initialised
	if (sceneQueryRay != NULL)
	{
		// setup the query object
		sceneQueryRay->setRay(ray);

		// execute the query, returns a vector of hits
		if (sceneQueryRay->execute().size() <= 0)
		{
			// raycast did not hit an objects bounding box
			return false;
		}
	}
	else
	{
		// The raySceneQuery did not initialize properly.
		return false;
	}

	// Temporary storage variables.
	Ogre::Real tempClosestDistance = -1.0f;
	Ogre::Vector3 tempClosestResult;

	// Get the results from the ray Query
	Ogre::RaySceneQueryResult &rayQueryResult = sceneQueryRay->getLastResults();

	// Temp storage for the entity collided with.
	Ogre::Entity* collEntity = nullptr;

	// For each result in the ray Query results
	for (size_t index = 0; index < rayQueryResult.size(); index++)
	{
		// stop checking if we have found a raycast hit that is closer than all remaining entities
		if ((tempClosestDistance >= 0.0f) &&
			(tempClosestDistance < rayQueryResult[index].distance))
			break;

		// only check this result if its a hit against an entity
		if ((rayQueryResult[index].movable != NULL) &&
			(rayQueryResult[index].movable->getMovableType().compare("Entity") == 0))
		{
			// get the entity to check
			collEntity = static_cast<Ogre::Entity*>(rayQueryResult[index].movable);

			// mesh data to retrieve         
			size_t indexCount;
			Ogre::Vector3* vertices = new Ogre::Vector3();
			unsigned long* indices = NULL;

			// get the mesh information
			GetMeshInformation(collEntity, vertices, indexCount, indices,
				collEntity->getParentNode()->_getDerivedPosition(),
				collEntity->getParentNode()->_getDerivedOrientation(),
				collEntity->getParentNode()->_getDerivedScale());

			// test for hitting individual triangles on the mesh
			bool newClosestPolyFound = false;
			for (int i = 0; i < static_cast<int>(indexCount); i += 3)
			{
				// check for a hit against this triangle
				std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]],
					vertices[indices[i + 1]], vertices[indices[i + 2]], true, false);

				// if it was a hit, check if its the closest
				if (hit.first)
				{
					if ((tempClosestDistance < 0.0f) ||
						(hit.second < tempClosestDistance))
					{
						// this is the closest so far, save it off
						tempClosestDistance = hit.second;
						newClosestPolyFound = true;
					}
				}
			}

			// free the verticies and indicies memory
			delete[] vertices;
			delete[] indices;

			// if we found a new closest raycast for this object, update the
			// tempClosestResult before moving on to the next object.
			if (newClosestPolyFound)
				tempClosestResult = ray.getPoint(tempClosestDistance);
		}
	}

	// return the result
	if (tempClosestDistance >= 0.0f)
	{
		// raycast success
		result = tempClosestResult;
		collided = collEntity;
		return true;
	}
	else
		// raycast failed
		return false;
	
}

void RayCasting::GetMeshInformation(
	Ogre::Entity * entity, 
	Ogre::Vector3* &vertices, 
	size_t & indexCount, 
	unsigned long * &indices, 
	const Ogre::Vector3 & position, 
	const Ogre::Quaternion & orient, 
	const Ogre::Vector3 & scale)
{
	bool added_shared = false;
	size_t current_offset = 0;
	size_t shared_offset = 0;
	size_t next_offset = 0;
	size_t index_offset = 0;
	size_t vertexCount = indexCount = 0;

	Ogre::MeshPtr mesh = entity->getMesh();


	bool useSoftwareBlendingVertices = entity->hasSkeleton();

	if (useSoftwareBlendingVertices)
	{
		entity->_updateAnimation();
	}

	// Calculate how many vertices and indices we're going to need
	for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
	{
		Ogre::SubMesh* submesh = mesh->getSubMesh(i);

		// We only need to add the shared vertices once
		if (submesh->useSharedVertices)
		{
			if (!added_shared)
			{
				vertexCount += mesh->sharedVertexData->vertexCount;
				added_shared = true;
			}
		}
		else
		{
			vertexCount += submesh->vertexData->vertexCount;
		}

		// Add the indices
		indexCount += submesh->indexData->indexCount;
	}


	// Allocate space for the vertices and indices
	vertices = new Ogre::Vector3[vertexCount];
	indices = new unsigned long[indexCount];

	added_shared = false;

	// Run through the submeshes again, adding the data into the arrays
	for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
	{
		Ogre::SubMesh* submesh = mesh->getSubMesh(i);

		//----------------------------------------------------------------
		// GET VERTEXDATA
		//----------------------------------------------------------------

		  //Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
		Ogre::VertexData* vertex_data;

		//When there is animation:
		if (useSoftwareBlendingVertices)
			vertex_data = submesh->useSharedVertices ? entity->_getSkelAnimVertexData() : entity->getSubEntity(i)->_getSkelAnimVertexData();
		else
			vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;


		if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
		{
			if (submesh->useSharedVertices)
			{
				added_shared = true;
				shared_offset = current_offset;
			}

			const Ogre::VertexElement* posElem =
				vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

			Ogre::HardwareVertexBufferSharedPtr vbuf =
				vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

			unsigned char* vertex =
				static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

			// There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
			//  as second argument. So make it float, to avoid trouble when Ogre::Real will
			//  be comiled/typedefed as double:
			//      Ogre::Real* pReal;
			float* pReal;

			for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
			{
				posElem->baseVertexPointerToElement(vertex, &pReal);

				Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

				vertices[current_offset + j] = (orient * (pt * scale)) + position;
			}

			vbuf->unlock();
			next_offset += vertex_data->vertexCount;
		}


		Ogre::IndexData* index_data = submesh->indexData;
		size_t numTris = index_data->indexCount / 3;
		Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;

		bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);


		size_t offset = (submesh->useSharedVertices) ? shared_offset : current_offset;
		size_t index_start = index_data->indexStart;
		size_t last_index = numTris * 3 + index_start;

		if (use32bitindexes)
			for (size_t k = index_start; k < last_index; ++k)
			{
				indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
			}

		else
			for (size_t k = index_start; k < last_index; ++k)
			{
				indices[index_offset++] = static_cast<unsigned long>(pShort[k]) +
					static_cast<unsigned long>(offset);
			}

		ibuf->unlock();
		current_offset = next_offset;
	}
}
