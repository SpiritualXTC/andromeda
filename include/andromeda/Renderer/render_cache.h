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

		// Renderables
		virtual Boolean addRenderable(IRenderable * renderable, const std::string & group = "") = 0;
		virtual Boolean removeRenderable(IRenderable * renderable, const std::string & group = "") = 0;

		// Lights

		// Buffers
	};



	/*
		New Cache
	*/
	class RenderCache// : public IRenderableManager
	{
	public:
		RenderCache(Camera * _camera, IRenderableManager * renderManager);
		virtual ~RenderCache();


		Boolean hasObject(GameObject * object);
		Boolean addGameObject(GameObject * object);
		Boolean removeGameObject(GameObject * object);


		// Remove everything from the cache
		Boolean clearObjects();

		// Process an Object
		void process(GameObject * go);

		// Render Group Management
	//	std::shared_ptr<RenderableGroup> getRenderGroup(const std::string & group);

		// Interface
	//	Boolean addRenderable(IRenderable * renderable, const std::string & group = "") override;
	//	Boolean removeRenderable(IRenderable * renderable, const std::string & group = "") override;

	private:
		// Does the ID exist in the lookup table
		Boolean exists(UInt64 id);

		// Inserts the ID into the lookup table
		Boolean insert(UInt64 id);

		// Removes the ID from the lookup table
		Boolean erase(UInt64 id);




		Camera * _camera = nullptr;					// Pointer to the camera
		IRenderableManager * _renderManager = nullptr;


		// Lookup Table
		std::unordered_map<UInt64, Boolean> _table;

		// List of all Objects :: This is needed if the view get destroyed
		std::unordered_map<UInt64, GameObject*> _objects;
		//std::unordered_map<UInt64, std::shared_ptr<GameObject>> _objects;

		// Render Object Groups
		std::unordered_map<std::string, std::shared_ptr<RenderableGroup>> _groups;
	};

}


