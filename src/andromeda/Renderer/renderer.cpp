#include <andromeda/Renderer/renderer.h>

#include <assert.h>

#include <andromeda/Graphics/effect.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/layer.h>
#include <andromeda/Renderer/render_stage.h>


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
	_camera->setView(1.0f);
	_camera->setOrthogonal(1.0f, 0.01f, 1000.0f);

	// Create Cache
//	_cache = std::make_shared<RenderCache>(_camera.get());
}


/*

*/
Renderer::~Renderer()
{

}

/*
	Basic implementation for adding an Method
*/
Boolean Renderer::addMethod(const std::string & methodName, const std::shared_ptr<RenderStage> & method)
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

std::shared_ptr<RenderStage> Renderer::getRenderMethod(const std::string & methodName)
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

	std::shared_ptr<RenderStage> m;

	// Not Found?
	if (it == _methods.end())
	{
		// Create Basic RendererMethod
		m = std::make_shared<RenderStage>(getCamera());
		
		// Insert it
		_methods.insert({method, m});
	}
	else
		m = it->second;

	assert(m);

	// Gets the Render Group
//	std::shared_ptr<RenderableGroup> rg = _cache->getRenderGroup(renderGroup);

	// Add a Layer to the rendering method
//	m->addLayer(_camera, rg, effect, technique);
	
	m->addLayer(renderGroup, effect, technique);

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
//	assert(_cache);
	
	// Clear the Cache
//	_cache->clearObjects();
}



/*

*/
void Renderer::update()
{
	assert(_camera);
	assert(_sceneGraph);
	//	assert(_cache);

	// Update the Camera :: This is done during the notification when the camera is moved
//	_camera->update();



	// Process the Scene Graph
	//_sceneGraph->process(_cache);

	// Update All Render Stages
	for (const auto & method : _methods)
	{
		method.second->update(_sceneGraph.get());
	}
}


/*

*/
void Renderer::render()
{
	// Renders all the Stages
	for (const auto & method : _methods)
	{
		RenderStage * m = method.second.get();

		// Configure the Stage
		m->begin();

		// Render the Scene
		m->render();

		// Configure the Stage :: Example (Revert back to the Normal FrameBuffer)
		m->end();
	}


	/*
		For Example:
		Deferred Rendering would require at least, 2 render stage. 
			The first required stage requires setting the GBuffer up for rendering too
			The second required stage would setup the Lighting for rendering, while using the GBuffers' textures as the source for world geometry
	*/
}












