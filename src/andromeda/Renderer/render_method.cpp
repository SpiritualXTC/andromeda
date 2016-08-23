#include <andromeda/Renderer/renderer.h>

#include <andromeda/Renderer/layer.h>

using namespace andromeda;

/*

*/
RendererMethod::RendererMethod()
{

}

/*

*/
RendererMethod::RendererMethod(const std::shared_ptr<ILayerEnvironment> & enviroment)
	: _environment(enviroment)
{

}


/*

*/
RendererMethod::~RendererMethod()
{

}

/*

*/
std::shared_ptr<ILayer> RendererMethod::addLayer(const std::shared_ptr<Camera> & camera, const std::shared_ptr<RenderableGroup> & rg, const std::shared_ptr<Effect> & effect, const std::string & technique)
{
	// Create Layer
	std::shared_ptr<Layer> layer = std::make_shared<Layer>(camera, effect, rg);

	// Sets the Layers Technique
	if (technique.length() != 0)
		layer->setActiveTechnique(technique);

	// Add Layer
	_layers.push_back(layer);

	return layer;
}

/*

*/
void RendererMethod::begin()
{
	// Nothing
}

/*

*/
void RendererMethod::end()
{
	// Nothing
}

/*

*/
void RendererMethod::render()
{
	// Render all the layers
	for (const auto & layer : _layers)
		layer->render(_environment.get());
}
