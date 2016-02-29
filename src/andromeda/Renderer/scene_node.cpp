#include <andromeda/Renderer/scene_graph.h>

#include <algorithm>
#include <cassert>

using namespace andromeda;

/*

*/
SceneNode::SceneNode()
{

}

/*

*/
SceneNode::SceneNode(std::shared_ptr<IRenderable> renderable)
	: _renderable(renderable)
{
	assert(_renderable);
}


/*

*/
SceneNode::~SceneNode()
{

}


/*

*/
Boolean SceneNode::addNode(std::shared_ptr<IRenderable> renderable)
{
	SceneNode node(renderable);

	_nodes.push_back(std::move(node));

	return true;
}

/*

*/
Boolean SceneNode::removeNode(std::shared_ptr<IRenderable> renderable)
{
	Int32 id = renderable->id();

	// Search for Matching Renderables!
	auto rem = std::remove_if(_nodes.begin(), _nodes.end(), [id](SceneNode & n){return n.id() == id; });
	
	// Remove any matching.
	if (rem != _nodes.end())
		_nodes.erase(rem, _nodes.end());

	return true;
}


/*
	TEMPORARY!
	Crappy rendering
*/
Boolean SceneNode::render(Shader * shader, glm::mat4 & modelView)
{
	if (_renderable)
		_renderable->render(shader, modelView);

	for (auto & it : _nodes)
		it.render(shader, modelView);

	return true;
}


