#include "deferred_lighting_stage.h"

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>


#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/scene_graph_cache.h>

#include "../renderable_group.h"

#include "deferred_directional_light.h"
#include "deferred_lighting_environment.h"

using namespace andromeda;
using namespace andromeda::deferred;


/*

*/
DeferredLightingStage::DeferredLightingStage(const std::shared_ptr<ILayerEnvironment> & enviro, const std::shared_ptr<Effect> & effect, const std::string & directionalTechnique)
	: RenderStage(nullptr, enviro)
{
	// Create a custom Camera
//	_directionalCamera = std::make_shared<Camera>();
//	_directionalCamera->setOrthogonalScreen(-1.0f, 1.0f);
//	_directionalCamera->setView(-1.0f);

	getCamera()->setOrthogonalScreen(-1.0f, 1.0f);
	getCamera()->setView(-1.0f);


	// Create a custom RenderableGroup
//	_directionalLights = std::make_shared<RenderableGroup>("directional");




	// Adds a special layer for Directional Lights
	// Directional Lights use a completely different camera, and a special RenderableGroup
	std::shared_ptr<ILayer> layer = addLayer("directional", effect, directionalTechnique);

	_directionalLights = getCache()->getRenderGroup("directional");
}





/*

*/
void DeferredLightingStage::addDirectionalLight()
{
	// Only support for one directional light.
	if (_renderable)
		return;

	// Create Renderable
	_renderable = std::make_shared<deferred::DeferredDirectionalLight>();

	// Add to the Renderable Group
	_directionalLights->addRenderable(_renderable.get());
}