#include <andromeda/Renderer/scene_graph_cache.h>


#include <cassert>


#include <andromeda/Game/game_object.h>
#include <andromeda/Game/transform_component.h>

#include <andromeda/Math/region.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/scene_graph.h>
#include <andromeda/Renderer/transform.h>
#include <andromeda/Renderer/view.h>
#include <andromeda/Renderer/visibility.h>


using namespace andromeda;


/*

*/
SceneGraphCache::SceneGraphCache(View * view, IVisibility * visibility)
	: _view(view)
	, _visibility(visibility)
{
	assert(_view);

}


/*

*/
SceneGraphCache::~SceneGraphCache()
{

}






/*
	Is this object in the scene
*/
Boolean SceneGraphCache::hasObject(std::shared_ptr<GameObject> object)
{
	// Validate Object
	assert(object);

	return exists(object->getId());
}





/*
	Adds a game object
*/
Boolean SceneGraphCache::addGameObject(std::shared_ptr<GameObject> object)
{
	// Validate Object
	assert(object);

	// There may be a situation where an object should be rejected by a view for adding
	// An Example would be:
	/*
	View Main:
	- The Main Display

	Object A:
	- Is a display terminal for a CCTV camera. Camera A
	- It therefore has a view. View A
	- Camera A is directly facing Object A

	When Object A becomes active to View Main:
	- A Dynamic View is added to the view list
	- The Dynamic View will process the scene from it's POV
	- It will "see" Object A and activate Object A for View A


	Aspects of this scenario need to be prevented, while aspects need to be allowed:
	- A Dynamic View will not be able to be add to the view list multiple times [Handled by the renderer or view list]
	- It will also need some "smart" management. Such as a reference counter
	- The Dynamic View should be able to render itself. [Backbuffer swapping]
	*/

	// Execute a bunch of callbacks :: This may work better straight on the game object... but needs some "smart" mechanisms


	Boolean b = insert(object->getId());
	if (b)
		object->onViewActivate(_view);

	return b;
}


/*
	Removes a game object
*/
Boolean SceneGraphCache::removeGameObject(std::shared_ptr<GameObject> object)
{
	assert(object);

	Boolean b = erase(object->getId());
	if (b)
		object->onViewDeactivate(_view);
	
	return b;
}










/*
	Does it exist in the Table
*/
Boolean SceneGraphCache::exists(UInt64 id)
{
	auto it = _table.find(id);

	// Was the Key found?
	// Return the Value.
	// This allows keys that exist in the table to set to false, without the need for removal :: however removing is currently still a requirement while using unordered_map
	return it == _table.end() ? false : it->second;
}



/*
	Inserts the ID into the lookup table
*/
Boolean SceneGraphCache::insert(UInt64 id)
{
	auto & it = _table.insert_or_assign(id, true);

	return it.second;
}


/*
	Removes the ID from the lookup table
*/
Boolean SceneGraphCache::erase(UInt64 id)
{
	// Override Flag
	if (exists(id))
		_table[id] = false;

	// Erase from Map
	Size removed = _table.erase(id);

	// Return whether any elements were removed
	return removed > 0;
}


#if 0
/*
	this shouldn't be here....
*/
Boolean SceneGraphCache::visiblilityCheck(const std::shared_ptr<GameObject> & go)
{
	// Visibility Test
	const std::shared_ptr<ICamera> & camera = _view->camera();

	// Transform Component
	std::shared_ptr<ITransform> transform = go->getComponentPtr<TransformComponent>();

	if (!transform)
		return false;


	aFloat cam_size = 2.0f;
	aFloat obj_size = 0.5f;


//	const glm::vec3 & cam_pos = camera->position();
	const glm::vec3 & obj_pos = transform->position();

	const glm::vec4 cam_pos2 = camera->worldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	


	Region2f valid = Region2f(glm::vec2(cam_pos2.x - cam_size, cam_pos2.z - cam_size), glm::vec2(cam_pos2.x + cam_size, cam_pos2.z + cam_size));
	Region2f object = Region2f(glm::vec2(obj_pos.x - obj_size, obj_pos.z - obj_size), glm::vec2(obj_pos.x + obj_size, obj_pos.z + obj_size));
	
	return valid.overlap(object);
}
#endif



/*

*/
void SceneGraphCache::process(const std::shared_ptr<GameObject> & go)
{
	assert(go);

	

	// Cache Check :: Is it already in the cache
	Boolean cached = exists(go->getId());

	// Visible :: Does the object pass the visibility check
	Boolean visible = true;

	if (!! _visibility)
		visible = _visibility->isVisible(go);




	// Object is Visble && It's Cached.				:: Nothing needs to be done
	// Object is NOT Visible && It's NOT Cached		:: Nothing needs to be done
	if (visible == cached)
		return; //return visible | cached;


	if (visible)
	{
		//	log_debugp("SceneGraph: Object '%1%' entered screen space. Adding to cache", p->getName());
		addGameObject(go);
	}
	else
	{
		//	log_debugp("SceneGraph: Object '%1%' exited screen space. Removing from Cache", p->getName());
		removeGameObject(go);
	}


	/* 
		This should really return a Boolean, so the SceneGraph knows whether it needs to continue deeper.
		...
		At least when a heirarchial SceneGraph is in use rather than a linear/hashmap one :D

		return VISIBLE or CACHED;

		This means visible objects will process children, but will also allow invisible 
		objects that are still cached to be processed :: So they can be removed from the cache, alongside any child objects
	*/
	// return visible | cached;

	return;
}
