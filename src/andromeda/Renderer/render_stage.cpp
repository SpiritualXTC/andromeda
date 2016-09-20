#include <andromeda/Renderer/render_stage.h>

#include <andromeda/Renderer/layer.h>
#include <andromeda/Renderer/render_cache.h>
#include <andromeda/Renderer/scene_graph.h>

#include "renderable_group.h"

using namespace andromeda;


/*

*/
RenderStage::RenderStage(const std::shared_ptr<Camera> & camera, const std::shared_ptr<ILayerEnvironment> & enviroment)
	: _camera(camera)
	, _environment(enviroment)
{
	// Create the Camera
	if (! _camera)
		_camera = std::make_shared<Camera>();

	// Create the Cache
	_cache = std::make_shared<RenderCache>(_camera.get(), this);
}







/*

*/
RenderStage::~RenderStage()
{

}


/*

*/
std::shared_ptr<ILayer> RenderStage::addLayer(const std::string & renderGroup,
	const std::shared_ptr<Effect> & effect, const std::string & technique)
{
	// Gets the Render Group
//	std::shared_ptr<RenderableGroup> rg = _cache->getRenderGroup(renderGroup);
	RenderableGroup * rg = getRenderGroup(renderGroup);

	// Create Layer
	std::shared_ptr<Layer> layer = std::make_shared<Layer>(_camera, effect, rg);

	// Sets the Layers Technique
	if (technique.length() != 0)
		layer->setActiveTechnique(technique);

	// Add Layer
	_layers.push_back(layer);

	return layer;
}




/*

*/
void RenderStage::update(SceneGraph * sg)
{
	// OLD
//	sg->process(_cache);

	// Change Meh

	/*
		TODO:
		This is a tempory implementation. the full scope required for 
		processing hte scene graph, with the cache will take some work.

		Requirements:
		When a parent object - AND ALL of it's children are off-screen, then the parent is considered offscreen,
		however if even ONE child is visible, then the parent is considered onscreen [IE: visible]


		CURRENT:
		Process all children, in the graph
	*/


	// NEW
	// Iterate through the scene graph
	for (const auto & it : *sg)
	{
		_cache->process(it.second->getObject().get());
	}

}


/*

*/
void RenderStage::begin(RenderState & gs)
{
	// Nothing
}


/*

*/
void RenderStage::render(RenderState & state)
{
	// Begin the Stage
	begin(state);

	// Render all the layers
	for (const auto & layer : _layers)
		layer->render(_environment.get());

	// End the Stage
	end(state);
}


/*

*/
void RenderStage::end(RenderState & gs)
{
	// Nothing
}










/*
	TODO:
	RenderableGroups needs to be moved to a new class, with RenderStage acting as a facade
*/



/*
	Gets the RenderGroup
*/
RenderableGroup * RenderStage::getRenderGroup(const std::string & group)
{
	// Find the Group
	const auto & it = _renderGroups.find(group);

	// Found ??
	if (it != _renderGroups.end())
	{
		// Retrieve
		return it->second.get();
	}

	// Create and Insert
	std::unique_ptr<RenderableGroup> rg = std::make_unique<RenderableGroup>(group);
	_renderGroups[group] = std::move(rg);

	return _renderGroups[group].get();
}

/*
	Adds a renderable to a group
*/
Boolean RenderStage::addRenderable(IRenderable * renderable, const std::string & group)
{
	// Gets the Group
	RenderableGroup * rg = getRenderGroup(group);

	assert(rg);

	// Add Renderable
	rg->addRenderable(renderable);

	return true;
}

/*
	Removes a renderable from the group
*/
Boolean RenderStage::removeRenderable(IRenderable * renderable, const std::string & group)
{
	// Gets the Group
	RenderableGroup * rg = getRenderGroup(group);

	assert(rg);

	// Remove Renderable
	rg->removeRenderable(renderable);

	return true;
}