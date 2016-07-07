#pragma once

/*
	TODO:
	This file does NOT need to be exposed
*/

#include <memory>
#include <unordered_map>

#include <andromeda/stddef.h>

namespace andromeda
{
	class Camera;
	class View;
	
	class ITransform;
	class GameObject;
	
	class SceneGraph;
	class IVisibility;

	/*
		Extremely Basic Scene Graph Caching

		Contains the SceneGraph of objects that are for all intensive purposes... "visible"
	*/

	/*
		TODO:
		Rename this to something more appropriate
	*/
	class SceneGraphViewCache
	{
	public:
		SceneGraphViewCache(View * view, Camera * _camera);
		virtual ~SceneGraphViewCache();


		Boolean hasObject(std::shared_ptr<GameObject> object);
		Boolean addGameObject(std::shared_ptr<GameObject> object);
		Boolean removeGameObject(std::shared_ptr<GameObject> object);
		




		/*
			Removes all entities
		*/
		Boolean clearObjects();


		/*
			OLD
		*/
		void process(const std::shared_ptr<GameObject> & go);

		

	private:
		/*
			Does the ID exist in the lookup table
		*/
		Boolean exists(UInt64 id);


		/*
			Inserts the ID into the lookup table
		*/
		Boolean insert(UInt64 id);


		/*
			Removes the ID from the lookup table
		*/
		Boolean erase(UInt64 id);


		View * _view = nullptr;						// Pointer to the view that created this cache
		Camera * _camera = nullptr;					// Pointer to the camera



		std::unordered_map<UInt64, Boolean> _table;

		// List of all Objects :: This is needed if the view get destroyed
		std::unordered_map<UInt64, std::shared_ptr<GameObject>> _objects;
	};

}


