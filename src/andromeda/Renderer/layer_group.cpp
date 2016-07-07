#include <andromeda/Renderer/layer_group.h>

#include <andromeda/Renderer/scene_graph.h>

using namespace andromeda;





/*

*/
LayerGroup::LayerGroup(const std::string & name, const std::shared_ptr<SceneGraph> & sceneGraph, View * view)
	: _name(name)
	, _sceneGraph(sceneGraph)
{
	assert(_sceneGraph);

	// Create Camera
	_camera = std::make_shared<Camera>();

	// Create Cache
	_cache = std::make_shared<SceneGraphViewCache>(view, _camera.get());
}


/*

*/
LayerGroup::~LayerGroup()
{
	/*
		TODO:
		This will need to be focus tested with multiple views
	*/
	// The Cached SceneGraph will need to update objects internal reference counters
	_cache->clearObjects();
}


/*

*/
void LayerGroup::render()
{
	assert(_camera);
	assert(_cache);

	// Update the Camera
	_camera->update();

	// Process the Scene Graph
	_sceneGraph->process(_cache);
}





