#include <andromeda/Renderer/scene_graph_basic.h>

#include <cassert>

#include <algorithm>
#include <functional>

#include <andromeda/Game/game_object.h>
#include <andromeda/Renderer/render_cache.h>

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
	update():

	Updates all objects in the scene
*/
void BasicSceneGraph::update(const Float timeStep)
{
	for (const auto & p : _objects)
		p.second->update(timeStep);
}


/*
	process():

	Process the Scene with respect to the cache

	TODO:
	Remove Meh
*/
Boolean BasicSceneGraph::process(std::shared_ptr<RenderCache> & sgCache)
{
	// Iterate through all objects
	for (const auto & it : _objects)
	{
		sgCache->process(it.second);
	}

	return true;
}