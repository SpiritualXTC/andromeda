#include <andromeda/Renderer/scene_graph_hierarchy.h>

#include <andromeda/Game/game_object.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
SceneGraphHierarchy::SceneGraphHierarchy()
{

}


/*

*/
SceneGraphHierarchy::~SceneGraphHierarchy()
{

}


/*
	hasObject():

	Is an object with the name in the Scene Graph?
*/
Boolean SceneGraphHierarchy::hasObject(const std::string & name)
{
	// Search for the Node
	const auto & it = _nodes.find(name);

	// Node Found?
	return it != _nodes.end();
}


/*
	hasObject():

	Is the object in the Scene Graph? (Currently is only doing a name scan)
*/
Boolean SceneGraphHierarchy::hasObject(std::shared_ptr<GameObject> object)
{
	return hasObject(object->getName());
}


/*
	getNode():

	Gets the Node
*/
SceneGraphHierarchy::SceneGraphNode * SceneGraphHierarchy::getNode(const std::string & name)
{
	// Search for the Node
	const auto & it = _nodes.find(name);

	// Node Not Found?
	if (it == _nodes.end())
		return nullptr;

	// Return the GameObject
	return it->second;
}


/*
	getGameObject():

	Gets the Game Object
*/
std::shared_ptr<GameObject> SceneGraphHierarchy::getGameObject(const std::string & name)
{
	SceneGraphNode * node = getNode(name);

	// Return the GameObject
	return !!node ? node->getObject() : nullptr;
}


/*
	addGameObject():

	Adds a GameObject to the Root
*/
Boolean SceneGraphHierarchy::addGameObject(const std::shared_ptr<GameObject> & object)
{
	assert(!!object);

	// Add Child to Root
	return addGameObject(object, this);
}


/*
	addGameObject():

	Adds a GameObject to a Parent
*/
Boolean SceneGraphHierarchy::addGameObject(const std::shared_ptr<GameObject> & object, const std::string & parent)
{
	assert(!!object);

	// Adds to Parent
	SceneGraphNode * p = getNode(parent);

	// Validate Parent
	if (!p) return nullptr;

	// Add Child to Parent
	return addGameObject(object, p);;
}


/*
	addGameObject():

	Adds a GameObject to a Node
*/
Boolean SceneGraphHierarchy::addGameObject(const std::shared_ptr<GameObject> & object, SceneGraphNode * parent)
{
	// Validate Duplicate Node
	if (hasObject(object->getName()))
		return false;

	// Add to Parent
	SceneGraphNode * n = parent->add(object);

	// Failed to Add
	if (!n) return false;

	// Insert the Node into the Hashmap for Quick Lookup/Access
	_nodes.insert({ object->getName(), n });

	return true;
}


/*
	removeGameObject():

	Removes a GameObject from the SceneGraph
*/
Boolean SceneGraphHierarchy::removeGameObject(const std::string & name)
{
	// Get the Node
	SceneGraphNode * node = getNode(name);

	// Validate Node. Validate Parent
	if (!node || !node->getParent()) return false;

	// Remove Node from Parent.
	if (!node->getParent()->remove(node->getObject()))
		return false;

	// Remove from the Map
	_nodes.erase(name);

	return true;
}


/*
	removeGameObject():
	
	Removes a GameObject from the SceneGraph
*/
Boolean SceneGraphHierarchy::removeGameObject(const std::shared_ptr<GameObject> & object)
{
	return removeGameObject(object->getName());
}





