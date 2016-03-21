#include <andromeda/Renderer/scene_graph_cache.h>


#include <cassert>

#include <andromeda/Game/game_object.h>
#include <andromeda/Game/scene_component.h>

using namespace andromeda;


/*

*/
SceneGraphCache::SceneGraphCache(View * view)
	: _view(view)
{
	assert(_view);

}


/*

*/
SceneGraphCache::~SceneGraphCache()
{

}

/*
	Get Object By Name
*/
std::shared_ptr<GameObject> SceneGraphCache::getGameObject(const std::string & name)
{
	if (!hasObject(name))
		return nullptr;

	return _objects[name];
}


/*
	Is an object with this name in the scene
*/
Boolean SceneGraphCache::hasObject(const std::string & name)
{
	return _objects.find(name) != _objects.end();
}


/*
	Is this object in the scene
*/
Boolean SceneGraphCache::hasObject(std::shared_ptr<GameObject> object)
{
	std::shared_ptr<GameObject> p = getGameObject(object->getName());

	return p == object;
}





/*
	Adds a game object
*/
Boolean SceneGraphCache::addGameObject(std::shared_ptr<GameObject> object)
{
	// Validate Object
	assert(object);

	// Validate Name
	if (hasObject(object->getName()))
		return false;

	// Insert
	_objects[object->getName()] = object;

	// Exists?
	Boolean b = hasObject(object->getName());

	if (b)
	{
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


		object->onViewActivate(_view);
	}
	return b;
}


/*
	Removes a game object
*/
Boolean SceneGraphCache::removeGameObject(const std::string & name)
{
	return removeGameObject(getGameObject(name));
}


/*
	Removes a game object
*/
Boolean SceneGraphCache::removeGameObject(std::shared_ptr<GameObject> object)
{
	assert(object);

	// Get Name
	const std::string & name = object->getName();

	// Validate Name
	if (!hasObject(name))
		return false;

	// Erase
	_objects.erase(name);

	// Exists?
	Boolean b = hasObject(name);

	if (!b)
	{
		// Execute a bunch of callbacks

		object->onViewDeactivate(_view);
	}

	return b;
}



/*

*/
void SceneGraphCache::for_each(std::function<void(std::shared_ptr<GameObject>)> cb)
{
	// Iterate through all objects, execute the callback
	for (const auto & p : _objects)
		cb(p.second);
}


/*

*/
Boolean SceneGraphCache::process(std::shared_ptr<ITransform> transform, std::shared_ptr<ISceneGraph> source)
{
	assert(source);
	// Does a direct copy (crappy system)


	source->for_each(
		[this](std::shared_ptr<GameObject>& p)
	{
		// "Visibility Check" :: Determines whether the object is "on screen"
		// This needs to be a function attached to the view, either pass in via an Interface (IViewScanner...)
		//  + Flexible
		//  + Possible to Create a Default for a view
		// OR
		// The cache itself gets hardwired with the routine (Policy Design...)
		//  + Flexible
		//  + Possible to Create a default
		//  - Extra Boiler Plate Code
		//  - Requires a nasty template
		// OR
		// A Callback function on the View
		//	- may be harder to customize for specific needs
		// Either way, information needs to be packaged in some hidden way to determine whether an object is "visible" to a camera source
		Boolean visible = true;	

		// Cache Check :: Is it already in the cache
		Boolean cached = hasObject(p);

		/* 
			TEMPORARY: Activation State Flipper
			If active/cached, there is a 1/60 chance of it becoming deactivated
			If NOT active/cached, there is a 1/10 chance of it becoming activated
		*/
		if (rand() % (cached ? 60 : 10) < 1)
			visible = !cached;
		else
			visible = cached;


		// Object is Visble && It's Cached.				:: Nothing needs to be done
		// Object is NOT Visible && It's NOT Cached		:: Nothing needs to be done
		if (visible == cached)
			return;


		if (visible)
		{
		//	log_debugp("SceneGraph: Object '%1%' entered screen space. Adding to cache", p->getName());
			addGameObject(p);
		}
		else
		{
		//	log_debugp("SceneGraph: Object '%1%' exited screen space. Removing from Cache", p->getName());
			removeGameObject(p);
		}
	});

#if 0
	// Loop through objects
	for (const auto & it : source)
	{
		// "Visibility Check" :: Determines whether the object is "on screen"
		Boolean visible = true;
		Boolean cached = hasObject(it.first);

		// Object is Visble && It's Cached.				:: Nothing needs to be done
		// Object is NOT Visible && It's NOT Cached		:: Nothing needs to be done
		if (visible == cached)
			continue;


		if (visible)
		{
			log_debugp("SceneGraph: Object '%1%' entered screen space. Adding to cache", it.second->getName());
			addGameObject(it.second);
		}
		else
		{
			log_debugp("SceneGraph: Object '%1%' exited screen space. Removing from Cache", it.second->getName());
			removeGameObject(it.second);
		}
	}
#endif

	return true;
}