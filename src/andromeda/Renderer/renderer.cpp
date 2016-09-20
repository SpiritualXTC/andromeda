#include <andromeda/Renderer/renderer.h>

#include <assert.h>

#include <andromeda/Graphics/effect.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/layer.h>
#include <andromeda/Renderer/render_stage.h>

#include <andromeda/Renderer/render_state.h>

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
}


/*

*/
Renderer::~Renderer()
{

}

/*
	Basic implementation for adding an Method
*/
Boolean Renderer::addStage(const std::string & stageName, const std::shared_ptr<RenderStage> & stage)
{
	// Insert it
	_stages.insert({ stageName, stage });

	return true;
}


/*
	Check whether the renderer has a method with that specific name
*/
Boolean Renderer::hasRenderStage(const std::string & stage)
{
	const auto & it = _stages.find(stage);

	return it != _stages.end();
}

/*
	Gets the Render Method
*/
std::shared_ptr<RenderStage> Renderer::getRenderStage(const std::string & stage)
{
	const auto & it = _stages.find(stage);

	return it != _stages.end() ? it->second : nullptr;
}


/*
	Adds a layer to the specified RenderStage
*/
Boolean Renderer::addLayer(const std::string & stageName, const std::string & renderGroup, const std::shared_ptr<Effect> & effect, const std::string & technique)
{
	// Add a layer to the correct RenderStage
	// If no RenderMethod is found... create the basic one

	// Find RendererMethod
	const auto & it = _stages.find(stageName);

	std::shared_ptr<RenderStage> rs;

	// Not Found?
	if (it == _stages.end())
	{
		// Create Basic RendererMethod
		rs = std::make_shared<RenderStage>(getCamera());
		
		// Insert it
		addStage(stageName, rs);
	}
	else
		rs = it->second;

	assert(rs);

	// Add a Layer to the rendering method
	rs->addLayer(renderGroup, effect, technique);

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

	// Do any synchronisation here :)
	sync();

	// Update All Render Stages
	for (const auto & it : _stages)
	{
		RenderStage * rs = it.second.get();

		if (rs)
			rs->update(_sceneGraph.get());
	}
}


/*

*/
void Renderer::render(RenderState & state)
{
	// Renders all the Stages
	for (const auto & it : _stages)
	{
		RenderStage * rs = it.second.get();
		if (!rs) continue;

		// Push a new Graphics State
		state.push();

		// Render the Scene :: Configuration happens inside the function now.
		rs->render(state);

		// Pop the Graphics State
		state.pop();
	}


	/*
		For Example:
		Deferred Rendering would require at least, 2 render stages
			The first required stage requires setting the GBuffer up for rendering too
			The second required stage would setup the Lighting for rendering, while using the GBuffers' textures as the source for world geometry
	*/
}












