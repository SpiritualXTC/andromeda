#include <andromeda/Renderer/scene_graph.h>

#include <andromeda/Game/game_object.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;



/*

*/
SceneGraphNode::SceneGraphNode(SceneGraphNode * parent, const std::shared_ptr<GameObject> & o)
	: _parent(parent)
	, _object(o)
{

}


/*
	Adds a Node to the Child List
*/
SceneGraphNode * SceneGraphNode::add(const std::shared_ptr<GameObject> & child)
{
	// Create Child
	std::shared_ptr<SceneGraphNode> node = std::make_shared<SceneGraphNode>(this, child);

	// Get Current Child Count
	UInt32 count = _children.size();

	// Add the Child
	_children.push_back(node);

	// Validate
	if (count == _children.size())
		return false;

	// Return the New Node
	return node.get();
}


/*
	Removes a Node from the Child List
*/
Boolean SceneGraphNode::remove(const std::shared_ptr<GameObject> & child)
{
	// Get Current Child Count
	UInt32 count = _children.size();

	std::string name = child->getName();

	// Look for object with the matching name... and remove it
	_children.remove_if([&name](const std::shared_ptr<SceneGraphNode> & n) {return n->getObject()->getName() == name; });

	// Something Removed? The Current Size will be lower than the cached
	return _children.size() < count;
}


/*

*/
void SceneGraphNode::update(Float timeStep)
{
	// Update GameObject
	if (_object)
	{
		_object->update(timeStep);

		// Reset Bound Box to that of the Object
	}
	else
	{
		// Reset Bound Box to that of a negative extrusion
	}

	// Update Children
	for (auto & n : _children)
	{

		// Update Child Node
		if (n)
			n->update(timeStep);

		// Update Bounding Box
		// Modify the Bound Box so that it extends to include itself and the child
		// This is the VISIBILITY bounding box

	}
}
