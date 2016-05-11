#ifndef _ANDROMEDA_RENDERER_SCENE_GRAPH_CACHE_H_
#define _ANDROMEDA_RENDERER_SCENE_GRAPH_CACHE_H_

#include <memory>
#include <unordered_map>

#include <andromeda/stddef.h>

namespace andromeda
{
	class View;
	class ITransform;
	class GameObject;
	class SceneGraph;
	class IVisibility;

	/*
		Extremely Basic Scene Graph Caching

		Contains the SceneGraph of objects that are for all intensive purposes... "visible"

		This Probably SHOULD NOT Extend SceneGraph, as for all intensive purposes ... it's only needed for a quick lookup.
		Not even a pointer is needed (smart or otherwise)
	*/
	class SceneGraphCache
	{
	public:
		SceneGraphCache(View * view, IVisibility * visibility);
		virtual ~SceneGraphCache();


		Boolean hasObject(std::shared_ptr<GameObject> object);
		Boolean addGameObject(std::shared_ptr<GameObject> object);
		Boolean removeGameObject(std::shared_ptr<GameObject> object);
		

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





		/*
			Process the Source Graph to manipulate the cache
		*/
		//Boolean process(std::shared_ptr<ITransform> transform, std::shared_ptr<SceneGraph> source);


		/*
		
		*/
		void process(const std::shared_ptr<GameObject> & go);


//		Boolean visiblilityCheck(const std::shared_ptr<GameObject> & go);


	private:
		View * _view = nullptr;						// Pointer to the view that created this cache
		IVisibility * _visibility = nullptr;		// Pointer to the visibility check used for the view, by this cache
			
		std::unordered_map<UInt64, Boolean> _table;
	};

}

#endif
