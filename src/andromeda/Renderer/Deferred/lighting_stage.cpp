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
}



/*

*/
void DeferredLightingStage::setRenderable(const std::shared_ptr<IRenderable> & renderable)
{
	// This is just a hack.
	RenderableGroup * dl = getRenderGroup("directional");

	dl->addRenderable(renderable.get());
}
