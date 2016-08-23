#include <andromeda/Renderer/renderer.h>

#include <assert.h>

#include <andromeda/Graphics/effect.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/layer.h>


#include <andromeda/Renderer/scene_graph.h>
#include <andromeda/Renderer/scene_graph_cache.h>	// TODO rename to RenderCache

#include "renderable_group.h"

using namespace andromeda;




/*

*/
Renderer::Renderer(const std::shared_ptr<SceneGraph> & sg)
	//: _camera(camera)
	: _sceneGraph(sg)
{
	//assert(camera);
	assert(sg);

	// Create Camera
	_camera = std::make_shared<Camera>();

	// Create Cache
	_cache = std::make_shared<RenderCache>(_camera.get());
}


/*

*/
Renderer::~Renderer()
{

}

/*
	Basic implementation for adding an Method
*/
Boolean Renderer::addMethod(const std::string & methodName, const std::shared_ptr<RendererMethod> & method)
{
	// Insert it
	_methods.insert({ methodName, method });

	return true;
}


/*
	Check whether the renderer has a method with that specific name
*/
Boolean Renderer::hasRenderMethod(const std::string & methodName)
{
	const auto & it = _methods.find(methodName);

	return it != _methods.end();
}

std::shared_ptr<RendererMethod> Renderer::getRenderMethod(const std::string & methodName)
{
	const auto & it = _methods.find(methodName);

	return it != _methods.end() ? it->second : nullptr;
}


/*

*/
Boolean Renderer::addLayer(const std::string & method, const std::string & renderGroup, const std::shared_ptr<Effect> & effect, const std::string & technique)
{
	// Add a layer to the correct RenderMethod
	// If no RenderMethod is found... create a simple one

	// Find RendererMethod
	const auto & it = _methods.find(method);

	std::shared_ptr<RendererMethod> m;

	// Not Found?
	if (it == _methods.end())
	{
		// Create Basic RendererMethod
		m = std::make_shared<RendererMethod>();
		
		// Insert it
		_methods.insert({method, m});
	}
	else
		m = it->second;

	assert(m);

	// Gets the Render Group
	std::shared_ptr<RenderableGroup> rg = _cache->getRenderGroup(renderGroup);

	// Add a Layer to the rendering method
	m->addLayer(_camera, rg, effect, technique);
	
	return true;
}



/*

*/
void Renderer::resize(Float width, Float height)
{
	// Resize the Camera
	_camera->resize(width, height);

	// Call the onResize event
	onResize(width, height);
}


/*

*/
void Renderer::clear()
{
	assert(_cache);
	
	// Clear the Cache
	_cache->clearObjects();
}



/*

*/
void Renderer::update()
{
	assert(_camera);
	assert(_cache);
	assert(_sceneGraph);

	// Update the Camera
	_camera->update();

	// Process the Scene Graph
	_sceneGraph->process(_cache);
}


/*

*/
void Renderer::render()
{
	// Renders all the methods

	for (const auto & method : _methods)
	{
		RendererMethod * m = method.second.get();


		m->begin();

		// Render the Scene
		m->render();

		// Configure the Method :: Example (Revert back to the Normal FrameBuffer)
		m->end();
	}


	/*
		For Example:
		Deferred Rendering would require, 2 rendering methods. 
			The first would setup the GBuffer for rendering.
			The second would setup the Lighting for rendering, while using the GBuffers' textures as the source for world geometry
	*/
}












