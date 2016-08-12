#include "deferred_lighting_method.h"

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>


#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Renderer/camera.h>

#include "../renderable_group.h"

#include "deferred_directional_light.h"
#include "deferred_gbuffer_layer_extension.h"

using namespace andromeda;
using namespace andromeda::deferred;


/*

*/
DeferredRendererLightingMethod::DeferredRendererLightingMethod(std::shared_ptr<IFrameBuffer> & gBuffer, const std::shared_ptr<Effect> & effect, const std::string & directionalTechnique)
	: _gBuffer(gBuffer)
{
	// Create a custom Camera
	_directionalCamera = std::make_shared<Camera>();
	_directionalCamera->setOrthogonalScreen(-1.0f, 1.0f);
	_directionalCamera->setView(-1.0f);

	// Create a custom RenderableGroup
	_directionalLights = std::make_shared<RenderableGroup>("directional");


	// Adds a special layer for Directional Lights
	// Directional Lights use a completely different camera, and a special RenderableGroup
	std::shared_ptr<ILayer> layer = addLayer(_directionalCamera, _directionalLights, effect, directionalTechnique);

	layer->addExtension(std::make_shared<DeferredGBufferLayerExtension>(_gBuffer));
}





/*

*/
void DeferredRendererLightingMethod::addDirectionalLight()
{
	// Only support for one directional light.
	if (_renderable)
		return;

	// Create Renderable
	_renderable = std::make_shared<deferred::DeferredRendererDirectionalLight>();

	// Add to the Renderable Group
	_directionalLights->addRenderable(_renderable.get());
}