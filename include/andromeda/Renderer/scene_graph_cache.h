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

#if 0
	/*
		Extremely Basic Scene Graph Caching

		Contains the SceneGraph of objects that are for all intensive purposes... "visible"
	*/

	/*
		TODO:
		Rename this to something more appropriate

		RenderCache

		Add a few interfaces to access specific areas of this class

		IRenderableManager
		IGameObjectManager
	*/
	class SceneGraphCache
	{
	public:
		SceneGraphCache(View * view, Camera * _camera);
		virtual ~SceneGraphCache();


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


#endif






	class IRenderable;
	class RenderableGroup;


	/*
		This interface is purely to make changes made in certain areas a little less clusterfucky
	*/
	class IRenderableManager
	{
	public:
		IRenderableManager() {}
		virtual ~IRenderableManager() {}

		virtual Boolean addRenderable(IRenderable * renderable, const std::string & group = "") = 0;
		virtual Boolean removeRenderable(IRenderable * renderable, const std::string & group = "") = 0;
	};



	/*
		New Cache
	*/
	class RenderCache : public IRenderableManager
	{
	public:
		RenderCache(Camera * _camera);
		virtual ~RenderCache();


		Boolean hasObject(std::shared_ptr<GameObject> object);
		Boolean addGameObject(std::shared_ptr<GameObject> object);
		Boolean removeGameObject(std::shared_ptr<GameObject> object);


		// Remove everything from the cache
		Boolean clearObjects();


		/*
			Needs to be tweaked

			TODO:
			The SceneGraph abstract class and the RenderCache need to be tweaked for better access.

			Currently it is:

			begin SceneGraph.process(cache)
				for all objects in SceneGraph
					cache.process(object)
			end 


			should be:

			begin RenderCache.process()
				for (all objects in this.sceneGraph.objects())
					process(object);
			end
		*/
		void process(const std::shared_ptr<GameObject> & go);




		// Render Group Management
		std::shared_ptr<RenderableGroup> getRenderGroup(const std::string & group);

		Boolean addRenderable(IRenderable * renderable, const std::string & group = "") override;
		Boolean removeRenderable(IRenderable * renderable, const std::string & group = "") override;

	private:
		// Does the ID exist in the lookup table
		Boolean exists(UInt64 id);


		// Inserts the ID into the lookup table
		Boolean insert(UInt64 id);


		// Removes the ID from the lookup table
		Boolean erase(UInt64 id);


		Camera * _camera = nullptr;					// Pointer to the camera



		std::unordered_map<UInt64, Boolean> _table;

		// List of all Objects :: This is needed if the view get destroyed
		std::unordered_map<UInt64, std::shared_ptr<GameObject>> _objects;

		// Render Object Groups
		std::unordered_map<std::string, std::shared_ptr<RenderableGroup>> _groups;
	};

}


