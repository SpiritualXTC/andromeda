#pragma once

#include <memory>


#include <andromeda/glm.h>

#include <andromeda/stddef.h>

#include "renderable.h"

namespace andromeda
{
	// Forward Declarations
	class GameObject;

	class RenderCache;


	/*
		This may look a little messy for awhile... while testing the iterators :)

		Especially... as the iterator NEEDS to be abstract ... that is, reading from the iterator 
		is exactly the same no matter what type of container is in use.
	*/




	/*
		Once the Heirarchy SceneGraph is tested... remove this one.
	*/
	class SceneGraph
	{
	public:


	public:
		SceneGraph() {}
		virtual ~SceneGraph() {}

		virtual std::shared_ptr<GameObject> getGameObject(const std::string & name) = 0;

		virtual Boolean hasObject(const std::string & name) = 0;
		virtual Boolean hasObject(std::shared_ptr<GameObject> object) = 0;


		virtual Boolean addGameObject(const std::shared_ptr<GameObject> & object) = 0;
		virtual Boolean addGameObject(const std::shared_ptr<GameObject> & object, const std::string & parent) { return false; };	// THIS IS SUPPOSED TO BE PURE VIRTUAL :)

		virtual Boolean removeGameObject(const std::string & name) = 0;
		virtual Boolean removeGameObject(const std::shared_ptr<GameObject> & object) = 0;

		virtual const UInt32 getObjectCount() const = 0;

	

		virtual std::shared_ptr<GameObject> operator[](const char * const name) = 0;

		virtual void update(const Float timeStep) = 0;


		/*
			TODO:
			These really shouldn't be here.
			Access should be done via a begin/end function to allow for better iteration
		*/
		virtual Boolean process(std::shared_ptr<RenderCache> & sgCache) = 0;


	};




}

