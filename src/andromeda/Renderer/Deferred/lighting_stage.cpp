#include "lighting_stage.h"

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>


#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/render_cache.h>

#include "../renderable_group.h"

#include "directional_light.h"
#include "lighting_environment.h"

using namespace andromeda;
using namespace andromeda::deferred;

/*
	TODO:
	Add a RenderStage that DOESN'T use any SceneGraph / RenderCaching mechanism... that way the hack below wont feel so dirty :)
*/

/*

*/
DeferredLightingStage::DeferredLightingStage(const std::shared_ptr<ILayerEnvironment> & enviro, const std::shared_ptr<Effect> & effect, const std::string & directionalTechnique)
	: RenderStage(nullptr, enviro)
{
	// Setup Camera
	getCamera()->setOrthogonalScreen(-1.0f, 1.0f);
	getCamera()->setView(-1.0f);	// Why did this have to be negative?


	// Add the layer for directional lights
	std::shared_ptr<ILayer> layer = addLayer("directional", effect, directionalTechnique);

//	_directionalLights = getCache()->getRenderGroup("directional");
}



/*

*/
void DeferredLightingStage::setRenderable(const std::shared_ptr<IRenderable> & renderable)
{
	// This is just a hack.
	std::shared_ptr<RenderableGroup> dl = getCache()->getRenderGroup("directional");

	dl->addRenderable(renderable.get());
}


#if 0
/*

*/
void DeferredLightingStage::addDirectionalLight(const std::shared_ptr<LightDirectional> & directional)
{
	// Only support for one directional light.
	if (_renderable)
		return;

	// Create Renderable
	_renderable = std::make_shared<deferred::DeferredDirectionalLight>(directional);

	// Add to the Renderable Group
	_directionalLights->addRenderable(_renderable.get());
}
#endif