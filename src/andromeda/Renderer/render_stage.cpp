#include <andromeda/Renderer/render_stage.h>

#include <andromeda/Renderer/layer.h>
#include <andromeda/Renderer/render_cache.h>
#include <andromeda/Renderer/scene_graph.h>


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
	_cache = std::make_shared<RenderCache>(_camera.get());
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
	std::shared_ptr<RenderableGroup> rg = _cache->getRenderGroup(renderGroup);

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
	sg->process(_cache);

	// Change Meh

#if 0
	// NEW
	// Iterate through the scene graph
	for (const auto & it : sg)
	{

	}
#endif
}


/*

*/
void RenderStage::begin(GraphicsState & gs)
{
	// Nothing
}


/*

*/
void RenderStage::render(GraphicsState & gs)
{
	// Begin the Stage
	begin(gs);

	// Render all the layers
	for (const auto & layer : _layers)
		layer->render(_environment.get());

	// End the Stage
	end(gs);
}


/*

*/
void RenderStage::end(GraphicsState & gs)
{
	// Nothing
}