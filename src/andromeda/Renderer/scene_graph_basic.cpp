#include <andromeda/Renderer/scene_graph_basic.h>

#include <cassert>

#include <andromeda/Game/game_object.h>

using namespace andromeda;


/*

*/
BasicSceneGraph::BasicSceneGraph()
{

}


/*

*/
BasicSceneGraph::~BasicSceneGraph()
{

}

/*
	Get Object By Name
*/
std::shared_ptr<GameObject> BasicSceneGraph::getGameObject(const std::string & name)
{
	if (!hasObject(name))
		return nullptr;

	return _objects[name];
}


/*
	Is an object with this name in the scene
*/
Boolean BasicSceneGraph::hasObject(const std::string & name)
{
	return _objects.find(name) != _objects.end();
}


/*
	Is this object in the scene
*/
Boolean BasicSceneGraph::hasObject(std::shared_ptr<GameObject> object)
{
	std::shared_ptr<GameObject> p = getGameObject(object->getName());

	return p == object;
}





/*
	Adds a game object
*/
Boolean BasicSceneGraph::addGameObject(std::shared_ptr<GameObject> object)
{
	// Validate Object
	assert(object);

	// Validate Name
	if (hasObject(object->getName()))
		return false;

	// Insert
	_objects[object->getName()] = object;

	// Exists?
	return !! getGameObject(object->getName());
}


/*
	Removes a game object
*/
Boolean BasicSceneGraph::removeGameObject(const std::string & name)
{
	// Validate Name
	if (!hasObject(name))
		return false;

	// Erase
	_objects.erase(name);

	// Exists
	return ! getGameObject(name);
}


/*
	Removes a game object
*/
Boolean BasicSceneGraph::removeGameObject(std::shared_ptr<GameObject> object)
{
	assert(object);

	// Validate Object
	if (!hasObject(object))
		return false;

	// Erase
	_objects.erase(object->getName());

	// Exists
	return !getGameObject(object->getName());
}


/*

*/
void BasicSceneGraph::for_each(std::function<void(std::shared_ptr<GameObject>)> cb)
{
	for (const auto & p : _objects)
		cb(p.second);
}




/*

*/
void BasicSceneGraph::update(const Float timeStep)
{
	for (const auto & p : _objects)
		p.second->update(timeStep);
}




#if 0
/*

*/
Boolean BasicSceneGraph::process(std::shared_ptr<ITransform> transform, std::shared_ptr<ISceneGraph> sgCache)
{
	assert(sgCache);
	// Does a direct copy (crappy system)



	// Loop through objects
	for (const auto & it : _objects)
	{
		// "Visibility Check" :: Determines whether the object is "on screen"
		Boolean visible = true;
		Boolean cached = sgCache->hasObject(it.first);

		// Object is Visble && It's Cached.				:: Nothing needs to be done
		// Object is NOT Visible && It's NOT Cached		:: Nothing needs to be done
		if (visible == cached)
			continue;


		if (visible)
		{
			log_debugp("SceneGraph: Object '%1%' entered screen space, caching", it.second->getName());
			sgCache->addGameObject(it.second);
		}
		else
		{
			log_debugp("SceneGraph: Object '%1%' exited screen space, caching", it.second->getName());
			sgCache->removeGameObject(it.second);
		}
	}

	return true;
}
#endif